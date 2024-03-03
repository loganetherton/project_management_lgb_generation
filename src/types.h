//
// Created by Logan Etherton on 6/13/22.
//

#ifndef PYBIND_TYPES_H
#define PYBIND_TYPES_H

#include <vector>
#include <string>

bool DEBUG = true;
bool DEBUG_DATETIME = false;
bool DUMPJSONOBJECTS = true;


typedef std::vector<std::string> VecStr;
typedef std::vector<int> VecInt;
// Python DateTime compat
typedef std::chrono::system_clock::time_point DateTime;

auto dateTimeFormat = "%Y-%m-%d %H:%M:%S";
auto dateFormat = "%Y-%m-%d";

#endif //PYBIND_TYPES_H
