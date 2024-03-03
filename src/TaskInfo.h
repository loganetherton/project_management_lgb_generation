//
// Created by Logan Etherton on 6/21/22.
//

#ifndef PYBIND_TASKINFO_H
#define PYBIND_TASKINFO_H

#include <map>
#include <vector>
#include <utility>
#include <pybind11/chrono.h>
#include <chrono>
#include <iostream>
#include "BaseJsonStruct.h"
#include "Project.h"
#include "Task.h"

struct TaskInfo: public BaseJsonStruct {
  // From Project
  std::string creation_id;
  std::string first_name;
  std::string last_name;
  std::string validationId;
  std::string user_email;
  int relationship_id{0};
  std::string user_language;
  std::string creation;
  std::string completion;
  std::string classification_code;
  int estPoints{0};
  std::string sub_task_code;
  float avg_loe{0.0};
  bool from_userUpdates{false};
  bool is_shared{false};
  // From Task
  std::string lightGBMPrediction_start;
  std::string lightGBMPrediction_end;
  std::string type;
  int user_loe{0};
  int classifierPredication_loe{0};
  int override_total{0};
  std::string loe_per;
  // Calculated
  std::string classification_id;
  // Length of lightGBMPrediction
  int lou{0};
  std::string comments; // comments()
  std::vector<std::string> relationship_codes; // project_tags()
  std::string classification_name; // classification_name()
  std::string creation_with_classification;
  int quantity{1};
  float assignee_override_total{0.0};
  int assignee_loe{0};
  int projected_assignee_total{0};
  int assignee_error_id{0};
  std::string manually_evaluated_by;
  std::string manually_evaluated_by_name;
  std::string manually_evaluated_time;
  int user_id{0};
  std::string user_name{"Unassigned"};
  float total_pendingCount{0.0};
  float transaction_pendingCount{0.0};
  int transaction_estPoints{0};

  double getLengthOfLightGBMPrediction(Task& task) {
    auto startStr = task.lightGBMPrediction_start;
    auto endStr = task.lightGBMPrediction_end;

    auto parsedLightGBMPredictionStart = createTimePoint(startStr, dateFormat);
    auto parsedLightGBMPredictionEnd = createTimePoint(endStr, dateFormat);

    auto elapsedSeconds = getElapsedSeconds(parsedLightGBMPredictionStart, parsedLightGBMPredictionEnd);
    auto elapsedDays = durationSecondsToDays(elapsedSeconds);
    auto days = elapsedDays.count();
    return days;
  }

  void mapRelationshipCodes(const Project& project, const std::string& integrationType) {
    if (!project.current_relationship_code.empty()) {
      classification_code = project.current_relationship_code;
    } else {
      if (integrationType == "primary") {
        classification_code = project.classification_code;
        sub_task_code = project.sub_task_code;
      } else {
        classification_code = project.sub_task_code;
        sub_task_code = project.classification_code;
      }
    }
  }

  void setTaskInfo(Task& task) {
    lightGBMPrediction_start = task.lightGBMPrediction_start;
    lightGBMPrediction_end = task.lightGBMPrediction_end;
    type = task.type;
    user_loe = task.user_loe;
    classifierPredication_loe = task.classifierPredication_loe;
    override_total = task.override_total;
    loe_per = task.loe_per;
  }

  void setProjectKeys(Project& project) {
    creation_id = project.creation_id;
    first_name = project.first_name;
    last_name = project.last_name;
    validationId = project.validationId;
    user_email = project.user_email;
    relationship_id = project.relationship_id; // Also project_shared()
    user_language = project.user_language;
    creation = project.creation;
    completion = project.completion;
    classification_code = project.classification_code;
    estPoints = project.estPoints;
    sub_task_code = project.sub_task_code;
    avg_loe = project.avg_loe;
  }

  TaskInfo() = default;

  TaskInfo(const Project& project, const Task& task) {
    // From set_project_keys()
    creation_id = project.creation_id;
    first_name = project.first_name;
    last_name = project.last_name;
    validationId = project.validationId;
    user_email = project.user_email;
    relationship_id = project.relationship_id; // Also project_shared()
    user_language = project.user_language;
    creation = project.creation;
    completion = project.completion;
    classification_code = project.classification_code;
    estPoints = project.estPoints;
    sub_task_code = project.sub_task_code;
    avg_loe = project.avg_loe;

    // From set_task_info()
    lightGBMPrediction_start = task.lightGBMPrediction_start;
    lightGBMPrediction_end = task.lightGBMPrediction_end;
    type = task.type;
    user_loe = task.user_loe;
    classifierPredication_loe = task.classifierPredication_loe;
    override_total = task.override_total;
    loe_per = task.loe_per;
  }
};

#endif //PYBIND_TASKINFO_H
