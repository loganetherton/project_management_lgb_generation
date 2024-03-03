//
// Created by Logan Etherton on 6/9/22.
//

#ifndef PYBIND_DASHBOARD_H
#define PYBIND_DASHBOARD_H

#include <iostream>
#include <set>
#include <map>
#include <stdexcept>

#include <nlohmann/json.hpp>
#include <pybind11/stl_bind.h>
#include <pybind11/chrono.h>

#include "UserData.h"
#include "TeamData.h"
#include "ConfigReport.h"
#include "OrganizationContentClassification.h"
#include "Project.h"
#include "TaskInfo.h"
#include "ProgressInfo.h"

#include "types.h"


// For making opaque to Python
typedef std::map<int, UserData> UserDataMap;
typedef std::vector<Project> VecProject;


// @TODO Make properties private
class Dashboard: public BaseJsonStruct {
public:
  // @TODO MAKE PRIVATE
  std::map<int, std::string> user_list{};
  UserDataMap user_data{};

  // Public
  int organization_id = 0;
  std::string integration_type;
  int user_number = 0;
  DateTime start_date;
  DateTime end_date;
  std::string pendingCount_by;
  std::string start_cut_date = "2016-06-01";
  std::vector<int> user_id_list;

  TeamData team_data{};
  std::vector<Task> task_level_lightGBMPrediction_list;
  TaskList assigned_tasksRecords;
  // Tags from OrganizationContent
  std::map<int, OrganizationContentClassification> tags;
  ConfigReport configReport{};
  int velocity_goal = 0;
  int rate_goal = 0;
  int num_days = 0;
  Project project;
  VecProject projects;

  // Removed from Python, since it's just for redis caching
  //int task_index = 0;
  DateTime NOW;
  VecInt user_ids_list;
  VecStr project_level_keys{"creation_id", "first_name", "last_name", "validationId",
    "user_email", "relationship_id", "user_language", "creation", "completion",
    "classification_code", "estPoints", "sub_task_code", "avg_loe"};
  VecStr task_level_keys{"lightGBMPrediction_start", "lightGBMPrediction_end", "type", "user_loe", "classifierPredication_loe",
    "override_total", "loe_per"};

  Dashboard(int organizationId, const std::string &startDate, const std::string &endDate, const std::string &pendingCountBy) {
    UserData userData{};
    user_data[userData.user_id] = userData;
    organization_id = organizationId;
    start_date = createTimePoint(startDate, "start_date", dateFormat);
    end_date = createTimePoint(endDate, "end_date", dateFormat);
    pendingCount_by = pendingCountBy;
  }

  void appendToUserIdsList(const VecInt &userIds) {
    user_id_list = userIds;
  }

  /**
   * Return user ID from user_id_list if exists, else return 0
   * @param userId
   * @return
   */
  long getUserIdFromUserIdList(int userId) {
    auto it = std::find(user_id_list.begin(), user_id_list.end(), userId);
    if (it != user_id_list.end()) {
      auto index = it - user_id_list.begin();
      return index;
    }
    return -1;
  }

  void addUserIdIfNotExist(int userId) {
    auto index = getUserIdFromUserIdList(userId);
    if (index == -1) {
      return;
    }
    user_id_list.push_back(userId);
  }

  bool userIdExists(int userId) {
    auto iter = user_data.find(userId);
    if (iter != user_data.end()) {
      return true;
    }
    return false;
  }

  auto getUserById(int userId) {
    if (!userIdExists(userId)) {
      throw std::out_of_range("User not found");
    }
    return user_data[userId];
  }

  void addUserData(json &j) {
    UserData userData{j};
    user_data[userData.user_id] = userData;
  }

  void addTeamData(json &j) {
    TeamData teamData{j};
    team_data = teamData;
  }

  /**
   * Populate user data from raw JSON string
   * @param str
   * @return
   */
  void populateUserDataFromJsonStr(const char *str) {
    auto userDataJson = json::parse(str, str + strlen(str));
    if (!userDataJson.is_object()) {
      return;
    }
    for (auto &user: userDataJson) {
      addUserData(user);
    }
  }

  /**
   * Populate team data from raw JSON string
   * @param str
   * @return
   */
  void populateTeamDataFromJsonStr(const char *str) {
    auto teamDataJson = json::parse(str, str + strlen(str));
    addTeamData(teamDataJson);
  }

  /**
   * Populate OrganizationContent tags data from raw JSON string
   * @param str
   * @return
   */
  void populateOrganizationContentTagsFromJsonStr(const char *str) {
    auto organizationContentJson = json::parse(str, str + strlen(str));
    if (!organizationContentJson.is_object()) {
      return;
    }
    for (auto &[classificationId, content]: organizationContentJson.items()) {
      OrganizationContentClassification classification{content};
      tags[classification.CLASSIFICATION_ID] = classification;
    }
  }

  void addProject(json &j) {
    std::cout << "***********ADD PROJECT***********" << std::endl;
    std::cout << j.dump() << std::endl;
    project = Project(j);
    //projects.push_back(project);
  }

  void populateProjectFromJsonStr(const char *str) {
    auto projectJson = json::parse(str, str + strlen(str));
    addProject(projectJson);
  }

  void populateConfigReportFromJson(const char *str) {
    auto configReportJson = json::parse(str, str + strlen(str));
    configReport = ConfigReport(configReportJson);
  }

  void taskInfoComments(TaskInfo &taskInfo, Project &project) {
    for (auto &comment: project.comments) {
      if (!taskInfo.comments.empty()) {
        taskInfo.comments = taskInfo.comments + ";" + comment.comment;
      }
    }
  }

  void projectTags(int classificationId, TaskInfo &taskInfo) {
    if (tags.count(classificationId)) {
      auto classification = tags[classificationId];
      for (auto &relationshipCode: project.accepted_lightGBMPredictions) {
        auto it = std::find(classification.RELATIONSHIP_CODES.begin(), classification.RELATIONSHIP_CODES.end(), relationshipCode);
        if (it != classification.RELATIONSHIP_CODES.end()) {
          taskInfo.relationship_codes.push_back(relationshipCode);
        }
        taskInfo.classification_name = classification.NAME;
      }
    }
  }

  void calculateTaskInfo(Task& task, const std::string& classificationId, bool hasPendingTransactions) {
    auto taskInfo = TaskInfo();
    taskInfo.setProjectKeys(project);
    taskInfo.setTaskInfo(task);

    taskInfo.mapRelationshipCodes(project, integration_type);
    taskInfo.classification_id = classificationId;
    taskInfo.getLengthOfLightGBMPrediction(task);

    taskInfoComments(taskInfo, project);
    projectTags(std::stoi(classificationId), taskInfo);
    taskInfo.creation_with_classification = project.creation_id + "_" + classificationId;
    if (task.quantity) {
      taskInfo.quantity = task.quantity;
    }
    if (task.assignee_override_total != 0.0) {
      taskInfo.assignee_override_total = task.assignee_override_total;
    }
    if (task.assignee_loe) {
      taskInfo.assignee_loe = task.assignee_loe;
    }
    if (task.projected_assignee_total) {
      taskInfo.projected_assignee_total = task.projected_assignee_total;
    }
    if (!task.manually_evaluated_by.empty() && !task.manually_evaluated_time.empty() &&
      !task.manually_evaluated_by_name.empty()) {
      taskInfo.manually_evaluated_by = task.manually_evaluated_by;
      taskInfo.manually_evaluated_by_name = task.manually_evaluated_by_name;
      taskInfo.manually_evaluated_time = task.manually_evaluated_time;
    }
    if (task.user_id != 0 && task.user_id != -1) {
      taskInfo.user_id = task.user_id;
    }
    // @TODO set assignee_error_id from Python
    // @TODO call get_task_pendingCount_by_progress_date() from Python
    ProgressInfo progressInfo{};
    taskInfo.total_pendingCount = progressInfo.pendingCount;
    taskInfo.transaction_pendingCount = progressInfo.pendingCount;
    taskInfo.transaction_estPoints = progressInfo.transaction_estPoints;
  }

  /**
   * DashboardApi - iterate_assigned_tasksRecords()
   */
  void iterateAssignedTasks() {
    auto hasPendingTransactions = project.checkLoeEquity();
    auto assignedTasks = project.getAssignedTasks();

    for (auto &[classificationId, task]: assignedTasks) {
      calculateTaskInfo(task, classificationId, hasPendingTransactions);
    }
  }
};


#endif //PYBIND_DASHBOARD_H
