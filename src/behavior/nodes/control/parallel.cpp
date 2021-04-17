//
// Created by iWong on 26/3/2021.
//

#include "parallel.h"

namespace behavior {
    bool Parallel::DoEvaluate(const BevNodeInputParam &input) {
        bool ret = true;
        for(int i = 0; i < this->m_childNodeList.size(); ++i){
            BehaviorNode* node = this->GetChildNode(i);
            ret = node->Evaluate(input);
            if(!ret){
                ret = false;
                break;
            }
        }
        return ret;
    }

    int Parallel::DoTick(const BevNodeInputParam &input, BevNodeOutputParam &output) {
        bool successAll = true;
        bool successOne = false;
        bool failAll = true;
        bool failOne = false;
        int real_status = BT_RUNNING;
        for(int i = 0; i < this->m_childNodeList.size(); ++i){
            BehaviorNode* node = this->GetChildNode(i);
            int status = node->Tick(input, output);
            switch(status){
                case BT_SUCCESS:
                    failAll = false;
                    successOne = true;
                case BT_FAILURE:
                    successAll = false;
                    failOne = true;
                default:
                    ;
            }
        }
        if ((this->m_successPolicy == SUCCEED_ON_ALL && successAll) ||
            (this->m_successPolicy == SUCCEED_ON_ONE && successOne)) {
            real_status = BT_SUCCESS;
        } else if ((this->m_failPolicy == FAIL_ON_ALL && failAll) ||
                   (this->m_failPolicy == FAIL_ON_ONE && failOne)) {
            real_status = BT_FAILURE;
        }

        this->SetStatus(real_status);
        return real_status;
    }

    void Parallel::DoTransition(const BevNodeInputParam &input) {
        BehaviorNode::DoTransition(input);
    }

    void Parallel::SetSuccessPolicy(E_SUCCESS_POLICY policy) {
        this->m_successPolicy = policy;
    }

    void Parallel::SetFailPolicy(behavior::E_FAILURE_POLICY policy) {
        this->m_failPolicy = policy;
    }
}

