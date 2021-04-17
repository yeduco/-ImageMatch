//
// Created by iWong on 24/3/2021.
//

#include "condition_operator.h"
namespace behavior{
    bool ConditionAnd::ExternalCondition(const BevNodeInputParam &input) {
        bool ret = true;
        for(auto iter : this->m_children){
            ret = iter->ExternalCondition(input);
            if(!ret){
                break;
            }
        }
        return ret;
    }

    void ConditionAnd::PushChildren(ConditionBase *condition) {
        this->m_children.push_back(condition);
    }

    bool ConditionOr::ExternalCondition(const BevNodeInputParam &input) {
        bool ret = true;
        for(auto iter : this->m_children){
            ret = iter->ExternalCondition(input);
            if(ret){
                break;
            }
        }
        
        return ret;
    }

    void ConditionOr::PushChildren(ConditionBase *condition) {
        this->m_children.push_back(condition);
    }

    bool ConditionNot::ExternalCondition(const BevNodeInputParam &input) {
        return this->m_condition == nullptr || this->m_condition->ExternalCondition(input);
    }

    void ConditionNot::SetCondition(ConditionBase *condition) {
        this->m_condition = condition;
    }
}

