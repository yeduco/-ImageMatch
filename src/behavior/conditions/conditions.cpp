//
// Created by iWong on 24/3/2021.
//

#include "conditions.h"

namespace behavior {

    bool ExternalCondition(const BevNodeInputParam &input) {
        return true;
    }

    void ConditionBase::SetFieldName(const std::string &field_name) {
        this->m_fieldName = field_name;
    }

    std::string &ConditionBase::FieldName() {
        return this->m_fieldName;
    }

}