//
// Created by Logan Etherton on 6/9/22.
//

#ifndef PYBIND_TEAMDATA_H
#define PYBIND_TEAMDATA_H

#include <nlohmann/json.hpp>

#include "BaseJsonStruct.h"

struct TeamData: public BaseJsonStruct {
  int team_total_count = 0;
  int team_eligible_count = 0;
  int team_pendingCount = 0;
  int team_average_pendingCount = 0;
  int team_target_pendingCount = 0;
  int team_target_count = 0;
  int team_average_count = 0;
  int team_target_percentage = 0;
  int team_average_percentage = 0;
  int team_success_count = 0;
  int team_success_rate = 0;
  int team_efficiency_rate = 0;

  TeamData() = default;
  explicit TeamData(nlohmann::json& j) {
    team_total_count = setPropI(j, "team_total_count");
    team_eligible_count = setPropI(j, "team_eligible_count");
    team_pendingCount = setPropI(j, "team_pendingCount");
    team_average_pendingCount = setPropI(j, "team_average_pendingCount");
    team_target_pendingCount = setPropI(j, "team_target_pendingCount");
    team_target_count = setPropI(j, "team_target_count");
    team_average_count = setPropI(j, "team_average_count");
    team_target_percentage = setPropI(j, "team_target_percentage");
    team_average_percentage = setPropI(j, "team_average_percentage");
    team_success_count = setPropI(j, "team_success_count");
    team_success_rate = setPropI(j, "team_success_rate");
    team_efficiency_rate = setPropI(j, "team_efficiency_rate");
  }
};

#endif //PYBIND_TEAMDATA_H
