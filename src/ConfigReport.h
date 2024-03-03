//
// Created by Logan Etherton on 6/9/22.
//

#ifndef PYBIND_CONFIGREPORT_H
#define PYBIND_CONFIGREPORT_H

#include <iostream>
#include <map>
#include <nlohmann/json.hpp>

#include "BaseJsonStruct.h"

struct ConfigReportGoals: public BaseJsonStruct{
  int velocity{};
  int pendingCount{};

  explicit ConfigReportGoals() = default;

  explicit ConfigReportGoals(json& j) {
    velocity = setPropI(j, "velocity");
    pendingCount = setPropI(j, "pendingCount");
  }
};

struct ConfigReport: public BaseJsonStruct {
  std::string status;
  std::string print_form;
  std::string drill_down;
  std::string assignee_data_auto_reference;
  std::map<std::string, ConfigReportGoals> goals{};

  void addGoals(json& j) {
    if (!j.contains("goals")) {
      return;
    }
    auto goalsJson = j.at("goals");
    if (!goalsJson.is_object()) {
      return;
    }
    for (auto& [goalDate, goal]: goalsJson.items()) {
      goals[std::string(goalDate)] = ConfigReportGoals(goal);
    }
  }

  ConfigReport() = default;

  explicit ConfigReport(json& j) {
    status = setPropS(j, "status");
    print_form = setPropS(j, "print_form");
    drill_down = setPropS(j, "drill_down");
    assignee_data_auto_reference = setPropS(j, "assignee_data_auto_reference");
    addGoals(j);
  }
};

#endif //PYBIND_CONFIGREPORT_H
