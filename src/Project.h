//
// Created by Logan Etherton on 6/13/22.
//

#ifndef PYBIND_PROJECT_H
#define PYBIND_PROJECT_H

#include <map>
#include <vector>
#include <string>
#include <pybind11/chrono.h>
#include <nlohmann/json.hpp>

#include "types.h"
#include "BaseJsonStruct.h"
#include "Task.h"
#include "AssignedUser.h"
#include "Comment.h"


struct Project: public BaseJsonStruct {
  std::string _id;
  int organization_id{0};
  std::string creation_id;
  std::string creation;
  std::string updated;
  std::string last_name;
  int task_dependencies{0};
  DateTime completion_iso;
  std::string creation_status;
  std::string classification_code;
  float avg_loe{0.0};
  TaskList task_list;
  TaskList ancillary_list;
  int taskDependenciesSub{0};
  std::string user_language;
  std::string first_name;
  int estPoints{0};
  bool is_shared{false};
  DateTime creation_iso;
  std::string sub_task_code;
  std::string completion;
  std::string user_email;
  std::string validationId;
  int los{0};
  int relationship_id{0};
  bool from_userUpdates{false};
  int classification_id{0};
  std::string status;
  Comments comments{};
  DateTime created;
  int user_id{0};
  VecStr accepted_lightGBMPredictions{};
  float projected_total_pendingCount{0.0};
  float assignee_total_pendingCount{0.0};
  float projected_assignee_pendingCount{0.0};
  std::string current_relationship_code;

  TaskList handleList(json& j) {
    TaskList final_list{};
    for (auto &[classificationId, taskJson] : j.items()) {
      if (DEBUG) {
        std::cout << "cat id: " << classificationId << std::endl;
        std::cout << "task: " << taskJson << std::endl;
      }
      auto thisTask = Task(taskJson);
      final_list[classificationId] = thisTask;
    }
    return final_list;
  }

  TaskList getTaskListFromKey(json& j, const std::string& key) {
    std::cout << "***********HANDLE LIST***********" << std::endl;
    if (!j.contains(key)) {
      std::cout << key << " not present on project record" << std::endl;
      return TaskList{};
    }
    if (DEBUG) {
      std::cout << "***********HANDLE " << key << " LIST***********" << std::endl;
    }
    if (DUMPJSONOBJECTS) {
      std::cout << key << ":\n" << j.dump() << std::endl;
    }
    auto tasksJson = j.at(key);
    return handleList(tasksJson);
  }

  void handleComments(json& j) {
    if (!j.contains("comments")) {
      return;
    }
    auto commentsJson = j.at("comments");
    if (!commentsJson.is_array()) {
      return;
    }
    for (auto &c: commentsJson) {
      if (DUMPJSONOBJECTS) {
        std::cout << "Comment: " << commentsJson.dump() << std::endl;
      }
      auto comment = Comment(c);
      comments.push_back(comment);
    }
  }

  void handleAcceptedLightGBMPredictions(json& j, const std::string& key) {
    if (!j.contains(key)) {
      return;
    }
    auto acceptedJson = j.at(key);
    if (!acceptedJson.is_array()) {
      return;
    }
    for (auto &a: acceptedJson) {
      accepted_lightGBMPredictions.push_back(a);
    }
  }

  /**
   * Combine project.task_list and project.ancillary_list, removing duplicate tags on ancillary_list
   * @return
   */
  TaskList combineProjectTasks() {
    TaskList allTasks{};
    allTasks.insert(task_list.begin(), task_list.end());
    allTasks.insert(ancillary_list.begin(), ancillary_list.end());
    return allTasks;
  }

  TaskList getAssignedTasks() {
    auto allTasks = combineProjectTasks();
    TaskList assignedTasks{};
    for (auto& [classificationId, task]: allTasks) {
      if (task.accepted == "yes") {
        assignedTasks[classificationId] = task;
      }
    }
    return assignedTasks;
  }

  /**
   * Determine whether there are pending equity evaluations to be performed
   * @return bool
   */
  bool checkLoeEquity() {
    auto assignedTasks = getAssignedTasks();
    float total = 0.0;
    for (auto& [classificationId, task]: assignedTasks) {
      if (task.assignee_override_total > 0.0) {
        total += task.assignee_override_total;
      }
    }
    return assignee_total_pendingCount != total;
  }

  void iterateAssignedTasks() {
    bool hasPendingTransactions = checkLoeEquity();
    auto assignedTasks = getAssignedTasks();
    for (auto& [classificationId, task]: assignedTasks) {
      calculateTaskDict(task, hasPendingTransactions);
    }
  }

  void calculateTaskDict(Task task, bool hasPendingTransactions) {

  }

  Project() = default;

  explicit Project(json &j) {
    _id = setPropS(j, "_id");
    organization_id = setPropI(j, "organization_id");
    creation_id = setPropS(j, "creation_id");
    creation = setPropS(j, "creation");
    updated = setPropS(j, "updated");
    last_name = setPropS(j, "last_name");
    task_dependencies = setPropI(j, "task_dependencies");
    completion_iso = parseDateTimeJson(j, "completion_iso");
    creation_status = setPropS(j, "creation_status");
    classification_code = setPropS(j, "classification_code");
    avg_loe = setPropF(j, "avg_loe");
    task_list = getTaskListFromKey(j, "task_list");
    ancillary_list = getTaskListFromKey(j, "ancillary_list");
    taskDependenciesSub = setPropI(j, "taskDependenciesSub");
    user_language = setPropS(j, "user_language");
    first_name = setPropS(j, "first_name");
    estPoints = setPropI(j, "estPoints");
    is_shared = setPropB(j, "is_shared");
    creation_iso = parseDateTimeJson(j, "creation_iso");
    sub_task_code = setPropS(j, "sub_task_code");
    completion = setPropS(j, "completion");
    user_email = setPropS(j, "user_email");
    validationId = setPropS(j, "validationId");
    los = setPropI(j, "los");
    relationship_id = setPropI(j, "relationship_id");
    from_userUpdates = setPropB(j, "from_userUpdates");
    classification_id = setPropI(j, "classification_id");
    status = setPropS(j, "status");
    handleComments(j);
    created = parseDateTimeJson(j, "created");
    user_id = setPropI(j, "user_id");
    handleAcceptedLightGBMPredictions(j, "accepted_lightGBMPredictions");
    projected_total_pendingCount = setPropF(j, "projected_total_pendingCount");
    assignee_total_pendingCount = setPropF(j, "assignee_total_pendingCount");
    projected_assignee_pendingCount = setPropF(j, "projected_assignee_pendingCount");
  }
};


#endif //PYBIND_PROJECT_H
