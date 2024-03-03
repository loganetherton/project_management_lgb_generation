//
// Created by Logan Etherton on 6/10/22.
//

#ifndef PYBIND_MONGOTYPES_H
#define PYBIND_MONGOTYPES_H

#include <map>

typedef std::map<std::string, std::string> MongoOid;
typedef std::map<std::string, MongoOid> MongoId;

#endif //PYBIND_MONGOTYPES_H
