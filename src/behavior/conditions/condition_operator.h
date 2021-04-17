//
// Created by iWong on 24/3/2021.
//

#ifndef BEHAVIORTREE_CONDITION_OPERATOR_H
#define BEHAVIORTREE_CONDITION_OPERATOR_H
#include "conditions.h"
#include "vector"
namespace behavior{

    typedef std::vector<ConditionBase*> ChildrenVec;

    class ConditionAnd : public ConditionBase{
    public:
        ConditionAnd() = default;
        ~ConditionAnd() override = default;

        virtual bool ExternalCondition(const BevNodeInputParam& input);

        void PushChildren(ConditionBase* condition);


    private:
        ChildrenVec m_children;
    };

    class ConditionOr : public ConditionBase{
    public:
        ConditionOr() = default;
        ~ConditionOr() override = default;

        virtual bool ExternalCondition(const BevNodeInputParam& input);

        void PushChildren(ConditionBase* condition);

    private:
        ChildrenVec m_children;
    };

    class ConditionNot : public ConditionBase{
        public:
        ConditionNot() = default;
        ~ConditionNot() override = default;
        virtual bool ExternalCondition(const BevNodeInputParam& input);

        void SetCondition(ConditionBase* condition);

    private:
        ConditionBase* m_condition{};
    };


}


#endif //BEHAVIORTREE_CONDITION_OPERATOR_H
