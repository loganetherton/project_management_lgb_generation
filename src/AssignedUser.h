//
// Created by Logan Etherton on 6/17/22.
//

#ifndef PYBIND_ASSIGNEDUSER_H
#define PYBIND_ASSIGNEDUSER_H

#include "BaseJsonStruct.h"

struct AssignedUser: public BaseJsonStruct {
  DateTime date_time;
  int assigned_from{0};
  int assigned_to{0};
  int assigned_by{0};

  AssignedUser() = default;

  explicit AssignedUser(json &j) {
    assigned_from = setPropI(j, "assigned_from");
    assigned_to = setPropI(j, "assigned_to");
    assigned_by = setPropI(j, "assigned_by");
    date_time = parseDateTimeJson(j, "date_time");
  }
};


typedef std::vector<AssignedUser> VecAssignedUser;

#endif //PYBIND_ASSIGNEDUSER_H
