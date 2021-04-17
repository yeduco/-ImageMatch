//
// Created by iWong on 24/3/2021.
//

#ifndef BEHAVIORTREE_CONDITIONS_H
#define BEHAVIORTREE_CONDITIONS_H

#include "behavior_tree.h"
#include <string>
namespace behavior{
    struct AnyData;

    typedef AnyData BevNodeInputParam;
    typedef AnyData BevNodeOutputParam;

    class ConditionBase {
    public:
        virtual ~ConditionBase()= default;
        virtual bool ExternalCondition(const BevNodeInputParam& input) const = 0;
        void SetFieldName(const std::string &fieldName);
        std::string &FieldName();

    private:
        std::string m_fieldName;
    };
}

#endif //BEHAVIORTREE_CONDITIONS_H
