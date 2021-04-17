//
// Created by iWong on 24/3/2021.
//

#ifndef BEHAVIORTREE_SELECTOR_H
#define BEHAVIORTREE_SELECTOR_H

#include "behavior_tree.h"

namespace behavior {
    class Selector : public BehaviorNode {
    public:
        Selector() : m_currentIndex(0) {};

        ~Selector() override = default;

        bool DoEvaluate(const BevNodeInputParam &input) override;

        int DoTick(const BevNodeInputParam &input, BevNodeOutputParam &output) override;

        void DoTransition(const BevNodeInputParam &input) override;

        void UpdateCurrentIndex();

    private:
        int m_currentIndex;
    };
}


#endif //BEHAVIORTREE_SELECTOR_H
