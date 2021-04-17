//
// Created by iWong on 24/3/2021.
//

#include "selector.h"

namespace behavior {
    bool Selector::DoEvaluate(const BevNodeInputParam &input) {
        JUDGE_RETURN(this->m_childNodeList.empty() == false, false)
        int childSize = (int) m_childNodeList.size();
        int nextIndex = this->m_currentIndex;
        do {
            BehaviorNode* node = this->GetChildNode(m_currentIndex);
            if(node->Evaluate(input)) {
                this->m_currentIndex = nextIndex;
                return true;
            }
            nextIndex = (nextIndex + 1) % childSize;
        } while (nextIndex != this->m_currentIndex);
        return false;
    }

    int Selector::DoTick(const BevNodeInputParam &input, BevNodeOutputParam &output) {
        BehaviorNode* node = this->GetChildNode(this->m_currentIndex);
        int status = node->Tick(input, output);
        std::cout << "status " << status << std::endl;
        this->SetStatus(status);
        this->UpdateCurrentIndex();
        return status;
    }

    void Selector::UpdateCurrentIndex() {
        JUDGE_RETURN(this->GetStatus() == BT_SUCCESS, );
        this->m_currentIndex = (this->m_currentIndex + 1) % this->m_childNodeCount;
    }

    void Selector::DoTransition(const BevNodeInputParam &input) {
        BehaviorNode* node = this->GetChildNode(this->m_currentIndex);
        node->Transition(input);
        this->SetStatus(node->GetStatus());
    }
}



