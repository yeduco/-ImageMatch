//
// Created by iWong on 23/3/2021.
//

#include "behavior_tree.h"

#include <utility>
#include "conditions/conditions.h"

namespace behavior{

    bool BehaviorNode::Evaluate(const BevNodeInputParam &input) {
        return (this->m_nodePrecondition == nullptr || this->m_nodePrecondition->ExternalCondition(input)) && DoEvaluate(input);
    }

    void BehaviorNode::Transition(const BevNodeInputParam &input) {
        this->DoTransition(input);
    }

    int BehaviorNode::Tick(const BevNodeInputParam &input, BevNodeOutputParam &output) {
        return this->DoTick(input, output);
    }

    bool BehaviorNode::DoEvaluate(const BevNodeInputParam &input) {
        return true;
    }

    int BehaviorNode::DoTick(const BevNodeInputParam &input, BevNodeOutputParam &output) {
        return EBTStatus::BT_SUCCESS;
    }

    void BehaviorNode::DoTransition(const BevNodeInputParam &input) {
    }

    BehaviorNode::BehaviorNode() {
        this->m_nodePrecondition = nullptr;
        this->m_childNodeList.clear();
        this->m_parentNode = nullptr;
        this->m_childNodeCount = 0;
        this->m_status = BT_FAILURE;
    }

    void BehaviorNode::SetParentNode(BehaviorNode *node) {
        this->m_parentNode = node;
   }

    void BehaviorNode::PushChildNode(BevChildNode *node) {
        this->m_childNodeList.push_back(node);
        this->m_childNodeCount += 1;
    }

    void BehaviorNode::SetPrecondition(ConditionBase *condition) {
        this->m_nodePrecondition = condition;
    }

    void BehaviorNode::SetStatus(int status) {
        this->m_status = status;
    }

    int BehaviorNode::GetStatus() const {
        return this->m_status;
    }

    void BehaviorNode::SetFieldName(std::string fieldName) {
        this->m_fieldName = std::move(fieldName);
    }

    std::string &BehaviorNode::GetFileName() {
        return this->m_fieldName;
    }

    BehaviorNode *BehaviorNode::GetChildNode(int index) const {
        if (index < 0 || index > this->m_childNodeCount)
            return nullptr;

        return this->m_childNodeList[index]->m_pNode;
    }

    BevChildNode::BevChildNode(BehaviorNode *node, int priority) {
        this->m_pNode = node;
        this->m_priority = priority;
    }
}


