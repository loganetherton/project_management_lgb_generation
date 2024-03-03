//
// Created by Logan Etherton on 6/21/22.
//

#ifndef PYBIND_PROGRESSINFO_H
#define PYBIND_PROGRESSINFO_H

#include <string>
#include "BaseJsonStruct.h"

struct ProgressInfo: public BaseJsonStruct {
  int lou{0};
  int total_lou{0};
  int transaction_estPoints{0};
  float pendingCount{0.0};

  ProgressInfo() = default;
  ProgressInfo(int _lou, int _total_lou, int _transaction_estPoints, float _pendingCount) {
    lou = _lou;
    total_lou = _total_lou;
    transaction_estPoints = _transaction_estPoints;
    pendingCount = _pendingCount;
  }
};

#endif //PYBIND_PROGRESSINFO_H
