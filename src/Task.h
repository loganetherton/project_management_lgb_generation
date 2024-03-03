//
// Created by Logan Etherton on 6/17/22.
//

#ifndef PYBIND_TASK_H
#define PYBIND_TASK_H

#include "BaseJsonStruct.h"
#include "AssignedUser.h"

struct Task: public BaseJsonStruct {
  std::string lightGBMPrediction_end;
  int user_loe{0};
  int display_order{0};
  std::string lightGBMPrediction_start;
  int user_id{0};
  int classifierPredication_loe{0};
  std::string tasked_date;
  int override_total{0};
  std::string displayed;
  std::string accepted;
  std::string type;
  VecAssignedUser assigned_users{};
  std::string loe_per;
  int quantity{0};
  float assignee_override_total{0.0};
  int projected_assignee_total{0};
  int assignee_loe{0};
  int loe_per_unit{0};
  std::string manually_evaluated_by;
  std::string manually_evaluated_by_name;
  std::string manually_evaluated_time;

  void add_assigned_users(json &j) {
    std::cout << "***********ADD ASSIGNED USER***********" << std::endl;
    int i = 0;
    for (auto &a: j) {
      std::cout << "ADDING ASSIGNED USER: " << i << std::endl;
      assigned_users.push_back(AssignedUser(a));
      ++i;
    }
  }

  void handleAssignedUsers(json& j) {
    if (!j.contains("assigned_users")) {
      std::cout << "assigned_users not present on Task record" << std::endl;
      return;
    }
    auto jAssignedUsers = j.at("assigned_users");
    if (jAssignedUsers.is_array()) {
      add_assigned_users(j.at("assigned_users"));
    }
  }

  Task() = default;

  explicit Task(json &j) {
    if (DEBUG) {
      std::cout << "***********TASK***********" << std::endl;
      std::cout << j.dump() << std::endl;
    }

    lightGBMPrediction_end = setPropS(j, "lightGBMPrediction_end");
    user_loe = setPropI(j, "user_loe");
    display_order = setPropI(j, "display_order");
    lightGBMPrediction_start = setPropS(j, "lightGBMPrediction_start");
    user_id = setPropI(j, "user_id");
    classifierPredication_loe = setPropI(j, "classifierPredication_loe");
    tasked_date = setPropS(j, "tasked_date");
    override_total = setPropI(j, "override_total");
    displayed = setPropS(j, "displayed");
    accepted = setPropS(j, "accepted");
    type = setPropS(j, "type");
    handleAssignedUsers(j);
    loe_per = setPropS(j, "loe_per");
    quantity = setPropI(j, "quantity");
    assignee_override_total = setPropF(j, "assignee_override_total");
    projected_assignee_total = setPropI(j, "projected_assignee_total");
    assignee_loe = setPropI(j, "assignee_loe");
    loe_per_unit = setPropI(j, "loe_per_unit");
  }
};


typedef std::map<std::string, Task> TaskList;

#endif //PYBIND_TASK_H
