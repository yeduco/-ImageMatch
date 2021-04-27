//
// Created by iWong on 24/3/2021.
//

#ifndef BEHAVIORTREE_CONDITIONS_H
#define BEHAVIORTREE_CONDITIONS_H

#include "behavior_tree.h"
#include <string>
namespace behavior{

    class ConditionBase {
    public:
        virtual ~ConditionBase()= default;
        virtual bool ExternalCondition(const BevNodeInputParam& input) = 0;
        void SetFieldName(const std::string &fieldName);

        std::string &GetFieldName();

    private:
        std::string m_fieldName;
    };
}

#endif //BEHAVIORTREE_CONDITIONS_H
