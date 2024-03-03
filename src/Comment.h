//
// Created by Logan Etherton on 6/17/22.
//

#ifndef PYBIND_COMMENT_H
#define PYBIND_COMMENT_H

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>

#include "BaseJsonStruct.h"

struct Comment: public BaseJsonStruct {
  std::string comment;
  DateTime date_time;
  std::string full_name;

  Comment() = default;

  explicit Comment(json &j) {
    if (DUMPJSONOBJECTS) {
      std::cout << "Comment:\n" << j.dump() << std::endl;
    }
    comment = setPropS(j, "comment");
    date_time = parseDateTimeJson(j, "date_time");
    full_name = setPropS(j, "full_name");
  }
};


typedef std::vector<Comment> Comments;

#endif //PYBIND_COMMENT_H
