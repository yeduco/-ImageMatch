//
// Created by iWong on 22/3/2021.
//

#ifndef BEHAVIORTREE_ACTION_H
#define BEHAVIORTREE_ACTION_H
#include "behavior_tree.h"

namespace behavior {
    class BevActionNode : public BehaviorNode {
    public:
        BevActionNode() = default;

        ~BevActionNode() override = default;

    protected:
        virtual void DoEnter(const BevNodeInputParam &input, const BevNodeOutputParam &output);

        virtual void DoExit(const BevNodeInputParam &input, const BevNodeOutputParam &output);

        virtual int DoExecute(const BevNodeInputParam &input);

        int DoTick(const BevNodeInputParam &input, BevNodeOutputParam &output) override;

    private:
        void dump_log(const BevNodeInputParam &input);

    };
}

#endif //BEHAVIORTREE_ACTION_H
