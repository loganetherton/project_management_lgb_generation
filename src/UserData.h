//
// Created by Logan Etherton on 6/9/22.
//

#ifndef PYBIND_USERDATA_H
#define PYBIND_USERDATA_H

#include <iostream>
#include <nlohmann/json.hpp>

#include "BaseJsonStruct.h"

struct UserData: public BaseJsonStruct {
  int total_count = 0;
  int eligible_count = 0;
  std::string assignee_id = "Unassigned";
  float pendingCount = 0.0;
  int success_count = 0;
  int user_id = 0;
  std::string full_name = "Unassigned";
  int success_rate = 0;
  int efficiency_rate = 0;
  int user_id = 0;

  UserData() = default;
  explicit UserData(json& j) {
    total_count = setPropI(j, "total_count");
    eligible_count = setPropI(j, "eligible_count");
    assignee_id = setPropS(j, "assignee_id");
    pendingCount = setPropF(j, "pendingCount");
    success_count = setPropI(j, "success_count");
    user_id = setPropI(j, "user_id");
    full_name = setPropS(j, "full_name");
    success_rate = setPropI(j, "success_rate");
    efficiency_rate = setPropI(j, "efficiency_rate");
    user_id = setPropI(j, "user_id");
  }
};

#endif //PYBIND_USERDATA_H
