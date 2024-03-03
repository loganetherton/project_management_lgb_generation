//
// Created by Logan Etherton on 6/10/22.
//

#ifndef PYBIND_ORGANIZATIONCONTENTCLASSIFICATION_H
#define PYBIND_ORGANIZATIONCONTENTCLASSIFICATION_H

#include <iostream>
#include <map>
#include <vector>
#include "BaseJsonStruct.h"

struct OrganizationContentClassification: public BaseJsonStruct {
  std::string STATUS;
  std::string ORDERING_TYPE;
  std::string NAME;
  std::vector<std::string> RELATIONSHIP_CODES;
  std::string TYPE;
  int LOE = 0;
  int CLASSIFICATION_ID = 0;
  int PUBLIC_LISTED = 0;
  std::string LOE_PER;
  std::string REPORTING_TYPE;

  void setRelationshipCodes(json& j) {
    std::string key = "RELATIONSHIP_CODES";
    if (!j.contains(key)) {
      return;
    }
    auto relationshipCodesJson = j.at(key);
    if (!relationshipCodesJson.is_array()) {
      return;
    }
    for (const auto &relationshipCode: relationshipCodesJson) {
      RELATIONSHIP_CODES.push_back(relationshipCode);
    }
  }

  OrganizationContentClassification() = default;

  explicit OrganizationContentClassification(json& j) {
    STATUS = setPropS(j, "STATUS");
    ORDERING_TYPE = setPropS(j, "ORDERING_TYPE");
    NAME = setPropS(j, "NAME");
    setRelationshipCodes(j);
    TYPE = setPropS(j, "TYPE");
    LOE = setPropI(j, "LOE");
    CLASSIFICATION_ID = setPropI(j, "CLASSIFICATION_ID");
    PUBLIC_LISTED = setPropI(j, "PUBLIC_LISTED");
    LOE_PER = setPropS(j, "LOE_PER");
    REPORTING_TYPE = setPropS(j, "REPORTING_TYPE");
  }
};


#endif //PYBIND_ORGANIZATIONCONTENTCLASSIFICATION_H
