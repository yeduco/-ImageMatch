//
// Created by iWong on 25/3/2021.
//

#ifndef BEHAVIORTREE_SEQUENCE_H
#define BEHAVIORTREE_SEQUENCE_H
#include "behavior_tree.h"

namespace behavior{
    class Sequence : public BehaviorNode{
    public:
        Sequence():m_childCurrentIndex(0){};
        ~Sequence() override = default;
        bool DoEvaluate(const BevNodeInputParam &input) override;

        int DoTick(const BevNodeInputParam &input, BevNodeOutputParam &output) override;

        void DoTransition(const BevNodeInputParam &input) override;

    private:
        void UpdateNextIndex();

        int m_childCurrentIndex;

    };

}

#endif //BEHAVIORTREE_SEQUENCE_H
