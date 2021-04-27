//
// Created by iWong on 22/3/2021.
//

#ifndef BEHAVIORTREE_BEHAVIOR_NODE_H
#define BEHAVIORTREE_BEHAVIOR_NODE_H

#include <iostream>
#include <vector>
#include "test/test.h"
#include "image_matcher/ImageMatcher.h"
#include "behavior_struct.h"
namespace behavior {

#define JUDGE_RETURN(CONDITION, RETURN) if (!(CONDITION)){return RETURN;}

    class ConditionBase;

    class BehaviorNode;

    struct BevChildNode {
        explicit BevChildNode(BehaviorNode *node, int priority = 0);

        int m_priority;
        BehaviorNode *m_pNode;
    };

    typedef std::vector<BevChildNode *> BevChildNodeVec;

    class BehaviorNode {
    public:
        enum EBTStatus {
            BT_INVALID,
            BT_SUCCESS,
            BT_FAILURE,
            BT_RUNNING
        };

        BehaviorNode();

        virtual ~BehaviorNode() = default;

        bool Evaluate(const BevNodeInputParam &input);

        void Transition(const BevNodeInputParam &input);

        int Tick(const BevNodeInputParam &input, BevNodeOutputParam &output);

        void SetParentNode(BehaviorNode *node);

        void SetPrecondition(ConditionBase *condition);

        void PushChildNode(BevChildNode *node);

        BehaviorNode *GetChildNode(int index) const;

        void SetStatus(int status);

        int GetStatus() const;

        void SetFieldName(std::string fieldName);

        std::string &GetFieldName();

        BevChildNodeVec& GetChildNodeList();

        ConditionBase* GetPrecondition();

    protected:
        virtual bool DoEvaluate(const BevNodeInputParam &input);

        virtual int DoTick(const BevNodeInputParam &input, BevNodeOutputParam &output);

        virtual void DoTransition(const BevNodeInputParam &input);

        BevChildNodeVec m_childNodeList{};
        BehaviorNode *m_parentNode{};
        ConditionBase *m_nodePrecondition{};
        int m_childNodeCount;

    private:
        int m_status;
        std::string m_fieldName;
    };

}

#endif //BEHAVIORTREE_BEHAVIOR_NODE_H