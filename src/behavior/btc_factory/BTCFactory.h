//
// Created by iWong on 25/4/2021.
//

#ifndef _IMAGEMATCH_BTCFACTORY_H
#define _IMAGEMATCH_BTCFACTORY_H

#include "behavior/behavior_tree.h"
#include "include.h"

using namespace behavior;
using namespace rapidjson;

#define NEW_ACTION_NODE(type, classType) \
    if (actionName == type) \
    { \
        node = new classType; \
        node->SetFieldName(actionName);  \
    }

#define NEW_CONDITION_NODE(type, classType) \
    if (extPreCond == type) \
    { \
        conditionNode = new classType; \
        conditionNode->SetFieldName(extPreCond); \
    }

class  BTCFactory {
public:
    BTCFactory() = default;
    ~BTCFactory() = default;

    static BehaviorNode* GenerateAITree(const Document& aiTreeDoc);

    static BehaviorNode* CreateActionNode(const std::string& actionName, const Value& aiTreeJson);

    static BehaviorNode* CreateActionNode(const std::string& actionName, const Document& aiTreeDoc);

    static BehaviorNode* CreateControlNode(const std::string& controlName, const Value& aiTreeJson);

    static BehaviorNode* CreateControlNode(const std::string& controlName, const Document& aiTreeDoc);

    static void LoadActionNodeResource(BehaviorNode* node, const Value& aiTreeJson);

    static void LoadActionNodeResource(BehaviorNode* node, const Document& aiTreeDoc);

    static void LoadConditionNode(BehaviorNode* node, const Value &aiTreeJson);

    static void LoadConditionNode(BehaviorNode *node, const Document &aiTreeDoc);

    static void PrintfRootNode(BehaviorNode *node);

    static void PrintfChildNode(BevChildNodeVec &childNodeList);

};


#endif //_IMAGEMATCH_BTCFACTORY_H
