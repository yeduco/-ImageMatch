//
// Created by iWong on 22/3/2021.
//

#include "action.h"
namespace behavior {
    int BevActionNode::DoTick(const BevNodeInputParam &input, BevNodeOutputParam &output) {
        this->DoEnter(input, output);
        int status = this->DoExecute(input);
        this->DoExit(input, output);
        this->dump_log(input);
        return status;
    }

    void BevActionNode::DoEnter(const BevNodeInputParam &input, const BevNodeOutputParam &output) {
        std::cout << "enter [" << this->GetFieldName() << "]" << std::endl;
    }

    int BevActionNode::DoExecute(const BevNodeInputParam &input) {
        return BT_SUCCESS;
    }

    void BevActionNode::DoExit(const BevNodeInputParam &input, const BevNodeOutputParam &output) {
        std::cout << "exit [" << this->GetFieldName() << "]" << std::endl;
    }

    void BevActionNode::dump_log(const BevNodeInputParam &input) {
        std::cout << "nodeName:[" << this->GetFieldName() << "] running" << std::endl;
    }
}
