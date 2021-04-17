//
// Created by iWong on 25/3/2021.
//

#include "behavior_tree.h"
#include "sequence.h"

namespace behavior{

    bool behavior::Sequence::DoEvaluate(const BevNodeInputParam &input) {
        JUDGE_RETURN(this->m_childNodeList.empty() == false, false);
        BehaviorNode* node = this->GetChildNode(this->m_childCurrentIndex);
        return node->Evaluate(input);
    }

    int Sequence::DoTick(const BevNodeInputParam &input, BevNodeOutputParam &output) {
        BehaviorNode* node = this->GetChildNode(this->m_childCurrentIndex);
        int status = node->Tick(input, output);
        this->SetStatus(status);
        this->UpdateNextIndex();
        return status;
    }

    void Sequence::DoTransition(const BevNodeInputParam &input) {
        BehaviorNode::DoTransition(input);
    }

    void Sequence::UpdateNextIndex() {
        JUDGE_RETURN(this->GetStatus() == BT_SUCCESS,);
        this->m_childCurrentIndex = (this->m_childCurrentIndex + 1) % this->m_childNodeCount;
    }
}