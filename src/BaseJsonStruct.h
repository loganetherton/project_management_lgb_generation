//
// Created by Logan Etherton on 6/15/22.
//

#ifndef PYBIND_BASEJSONSTRUCT_H
#define PYBIND_BASEJSONSTRUCT_H

#include <fmt/core.h>
#include <fmt/chrono.h>
#include <nlohmann/json.hpp>
#include <pybind11/chrono.h>

#include "types.h"


using json = nlohmann::json;
using sysClock = std::chrono::system_clock;


struct BaseJsonStruct {
  int setPropI(json &j, const std::string &key) {
    if (!j.contains(key)) {
      return 0;
    }
    try {
      auto jVal = j.at(key);
      if (jVal.is_number()) {
        return int(jVal);
      } else if (jVal.is_string()) {
        return std::stoi(std::string(jVal));
      } else {
        return 0;
      }
    } catch (std::exception &e) {
      return 0;
    }
  }

  float setPropF(json &j, const std::string &key) {
    if (!j.contains(key)) {
      return 0.0;
    }
    try {
      auto jVal = j.at(key);
      if (jVal.is_number()) {
        return float(jVal);
      } else if (jVal.is_string()) {
        return std::stof(std::string(jVal));
      } else {
        return 0.0;
      }
    } catch (std::exception &e) {
      return 0.0;
    }
  }

  std::string setPropS(json &j, const std::string &key) {
    if (!j.contains(key)) {
      return "";
    }
    try {
      auto jVal = j.at(key);
      if (jVal.is_string()) {
        return jVal;
      } else if (jVal.is_number_integer()) {
        return std::to_string(int(jVal));
      } else if (jVal.is_number_float()) {
        return std::to_string(float(jVal));
      } else {
        return "";
      }
    } catch (std::exception &e) {
      return "";
    }
  }

  bool setPropB(json &j, const std::string &key) {
    if (!j.contains(key)) {
      return false;
    }
    try {
      auto jVal = j.at(key);
      if (jVal.is_boolean()) {
        return jVal;
      } else if (jVal.is_number()) {
        return bool(int(jVal));
      } else if (jVal.is_string()) {
        return bool(std::stoi(std::string(jVal)));
      } else {
        return false;
      }
    } catch (std::exception &e) {
      return false;
    }
  }

  sysClock::time_point createTimePoint(
    const std::string &val, const std::string &key, const char* dtFormat = dateTimeFormat
  ) {
    std::tm tm = {};
    std::istringstream ss((std::string(val)));
    ss.imbue(std::locale());
    ss >> std::get_time(&tm, dtFormat);
    if (ss.fail()) {
      fmt::print("Could not parse {}. Expected format: {}}", key, dtFormat);
      return sysClock::from_time_t(0);
    } else {
      if (DEBUG_DATETIME) {
        std::tm tmDebug = {};
        fmt::print("Incoming datetime string\n{} - {}\n", key, std::string(val));
        std::cout << "Parsed datetime: " << std::put_time(&tmDebug, "%c") << '\n';
      }
      std::time_t tt = std::mktime(&tm);
      return sysClock::from_time_t(tt);
    }
  }

  std::chrono::duration<double> getElapsedSeconds(sysClock::time_point begin, sysClock::time_point end) {
    return end - begin;
  }

  std::chrono::duration<double> durationSecondsToHours(std::chrono::duration<double> elapsedSeconds) {
    return elapsedSeconds / 60 / 60;
  }

  std::chrono::duration<double> durationSecondsToDays(std::chrono::duration<double> elapsedSeconds) {
    return elapsedSeconds / 60 / 60 / 24;
  }

  //sysClock::time_point createDateTime(
  //  const std::string &val, const std::string &key, const char* dtFormat = dateTimeFormat
  //) {
  //  std::tm tm = {};
  //  std::istringstream ss((std::string(val)));
  //  ss.imbue(std::locale());
  //  ss >> std::get_time(&tm, dtFormat);
  //  if (ss.fail()) {
  //    fmt::print("Could not parse {}. Expected format: {}}", key, dtFormat);
  //    return sysClock::from_time_t(0);
  //  } else {
  //    if (DEBUG_DATETIME) {
  //      std::tm tmDebug = {};
  //      fmt::print("Incoming datetime string\n{} - {}\n", key, std::string(val));
  //      std::cout << "Parsed datetime: " << std::put_time(&tmDebug, "%c") << '\n';
  //    }
  //    std::time_t tt = std::mktime(&tm);
  //    return sysClock::from_time_t(tt);
  //  }
  //}

  sysClock::time_point parseDateTimeJson(json &j, const std::string &key) {
    if (!j.contains(key)) {
      fmt::print("{} missing, so not datetime can be set\n", key);
      return sysClock::from_time_t(0);
    }
    const std::string val = j.at(key);
    return createTimePoint(val, key);
  }
};


#endif //PYBIND_BASEJSONSTRUCT_H
