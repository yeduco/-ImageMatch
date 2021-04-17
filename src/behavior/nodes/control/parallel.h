//
// Created by iWong on 26/3/2021.
//

#ifndef BEHAVIORTREE_PARALLEL_H
#define BEHAVIORTREE_PARALLEL_H
#include "behavior_tree.h"

namespace behavior{
    enum E_FAILURE_POLICY {
        FAIL_ON_ONE,
        FAIL_ON_ALL
    };

    // options when a parallel node is considered to be succeeded.
    // SUCCEED_ON_ONE: the node will return success as soon as one of its children succeeds.
    // SUCCEED_ON_ALL: the node will return success when all the node's children must succeed.
    enum E_SUCCESS_POLICY {
        SUCCEED_ON_ONE,
        SUCCEED_ON_ALL
    };
    class Parallel : public BehaviorNode{
    public:
        Parallel():m_failPolicy(FAIL_ON_ALL), m_successPolicy(SUCCEED_ON_ALL){};
        ~Parallel() override = default;

        bool DoEvaluate(const BevNodeInputParam &input) override;

        int DoTick(const BevNodeInputParam &input, BevNodeOutputParam &output) override;

        void DoTransition(const BevNodeInputParam &input) override;

        void SetSuccessPolicy(E_SUCCESS_POLICY policy);
        void SetFailPolicy(E_FAILURE_POLICY policy);

    private:
        E_SUCCESS_POLICY m_successPolicy;
        E_FAILURE_POLICY m_failPolicy;
    };
}

#endif //BEHAVIORTREE_PARALLEL_H
