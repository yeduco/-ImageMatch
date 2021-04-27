//
// Created by iWong on 25/4/2021.
//

#include <nodes/control/selector.h>
#include <nodes/control/sequence.h>
#include <nodes/control/parallel.h>
#include "BTCFactory.h"
#include "BTCName.h"
#include "ai_action/nodes/img_match_action.h"
#include "ai_action/nodes/img_match_condition.h"

using namespace image_match;
using namespace behavior;

BehaviorNode* BTCFactory::GenerateAITree(const Document& aiTreeDoc){
    JUDGE_RETURN(aiTreeDoc.HasMember("node_type"), nullptr);
    std::__cxx11::string nodeType = aiTreeDoc["node_type"].GetString();
    BehaviorNode* bevTree = nullptr;
    if(nodeType == BTCName::ActionNode) {
        std::__cxx11::string nodeAction = aiTreeDoc["node_action"].GetString();
        bevTree = CreateActionNode(nodeAction, aiTreeDoc);
    }
    if(nodeType == BTCName::ControlNode) {
        std::string nodeAction = aiTreeDoc["node_action"].GetString();
        bevTree = CreateControlNode(nodeAction, aiTreeDoc);
    }

    return bevTree;

}

BehaviorNode* BTCFactory::CreateActionNode(const std::string& _actionName, const Value& aiTreeJson){
    BehaviorNode* node = nullptr;
    std::__cxx11::string actionName = aiTreeJson["node_action"].GetString();
    NEW_ACTION_NODE(BTCName::ActionClickUI, AIIMClickAction);

    JUDGE_RETURN(node != nullptr, node);
    if (aiTreeJson.HasMember("node_resource")) {
        LoadActionNodeResource(node, aiTreeJson);
    }
    if (aiTreeJson.HasMember("ext_precond")) {
        LoadConditionNode(node, aiTreeJson);
    }
    JUDGE_RETURN(aiTreeJson.HasMember("node_tree"), node);
    const Value& nodeTree = aiTreeJson["node_tree"];
    SizeType len = nodeTree.Size();
    for(int i = 0; i < len; i++){
        const Value &nextTree = nodeTree[i];
        BehaviorNode *clientNode = nullptr;
        std::__cxx11::string clientNodeType = nextTree["node_type"].GetString();
        if (clientNodeType == BTCName::ActionNode) {
            std::__cxx11::string nodeAction = aiTreeJson["node_action"].GetString();
            clientNode = CreateActionNode(nodeAction, nextTree);
        } else if (clientNodeType == BTCName::ControlNode) {
            std::string nodeAction = aiTreeJson["node_action"].GetString();
            clientNode = CreateControlNode(nodeAction, nextTree);
        }
        node->PushChildNode(new BevChildNode(clientNode));
    }
    return node;
}

BehaviorNode* BTCFactory::CreateActionNode(const std::string& _actionName, const Document& aiTreeDoc){
    BehaviorNode* node = nullptr;
    std::__cxx11::string actionName = aiTreeDoc["node_action"].GetString();
    NEW_ACTION_NODE(BTCName::ActionClickUI, AIIMClickAction);

    JUDGE_RETURN(node != nullptr, node);
    if (aiTreeDoc.HasMember("node_resource")) {
        LoadActionNodeResource(node, aiTreeDoc);
    }
    if (aiTreeDoc.HasMember("ext_precond")) {
        LoadConditionNode(node, aiTreeDoc);
    }
    JUDGE_RETURN(!aiTreeDoc.HasMember("node_tree"), node);
    const Value& nodeTree = aiTreeDoc["node_tree"];
    SizeType len = nodeTree.Size();
    for(int i = 0; i < len; i++){
        const Value &nextTree = nodeTree[i];
        BehaviorNode *clientNode = nullptr;
        std::__cxx11::string clientNodeType = nextTree["node_type"].GetString();
        if (clientNodeType == BTCName::ActionNode) {
            std::__cxx11::string nodeAction = aiTreeDoc["node_action"].GetString();
            clientNode = CreateActionNode(nodeAction, nextTree);
        } else if (clientNodeType == BTCName::ControlNode) {
            std::string nodeAction = aiTreeDoc["node_action"].GetString();
            clientNode = CreateControlNode(nodeAction, nextTree);
        }
        node->PushChildNode(new BevChildNode(clientNode));
    }
    return node;
}

BehaviorNode* BTCFactory::CreateControlNode(const std::string& controlName, const Value& aiTreeJson){
    BehaviorNode* node = nullptr;
    std::__cxx11::string actionName = aiTreeJson["node_action"].GetString();
    NEW_ACTION_NODE(BTCName::ControlSelector, Selector);
    NEW_ACTION_NODE(BTCName::ControlSequence, Sequence);
    NEW_ACTION_NODE(BTCName::ControlParallel, Parallel);

    JUDGE_RETURN(node != nullptr, node);
    if (aiTreeJson.HasMember("ext_precond")) {
        LoadConditionNode(node, aiTreeJson);
    }
    JUDGE_RETURN(aiTreeJson.HasMember("node_tree"), node);
    const Value& nodeTree = aiTreeJson["node_tree"];
    SizeType len = nodeTree.Size();
    for(int i = 0; i < len; i++){
        const Value &nextTree = nodeTree[i];
        BehaviorNode *clientNode = nullptr;
        std::__cxx11::string clientNodeType = nextTree["node_type"].GetString();
        if (clientNodeType == BTCName::ActionNode) {
            std::__cxx11::string nodeAction = aiTreeJson["node_action"].GetString();
            clientNode = CreateActionNode(nodeAction, nextTree);
        } else if (clientNodeType == BTCName::ControlNode) {
            std::string nodeAction = aiTreeJson["node_action"].GetString();
            clientNode = CreateControlNode(nodeAction, nextTree);
        }
        node->PushChildNode(new BevChildNode(clientNode));
    }
    return node;
}

BehaviorNode* BTCFactory::CreateControlNode(const std::string& controlName, const Document& aiTreeDoc){
    BehaviorNode* node = nullptr;
    std::__cxx11::string actionName = aiTreeDoc["node_action"].GetString();
    NEW_ACTION_NODE(BTCName::ControlSelector, Selector);
    NEW_ACTION_NODE(BTCName::ControlSequence, Sequence);
    NEW_ACTION_NODE(BTCName::ControlParallel, Parallel);

    JUDGE_RETURN(node != nullptr, node);
    if (aiTreeDoc.HasMember("ext_precond")) {
        LoadConditionNode(node, aiTreeDoc);
    }
    JUDGE_RETURN(aiTreeDoc.HasMember("node_tree"), node);
    const Value& nodeTree = aiTreeDoc["node_tree"];
    SizeType len = nodeTree.Size();
    for(int i = 0; i < len; i++){
        const Value &nextTree = nodeTree[i];
        BehaviorNode *clientNode = nullptr;
        std::__cxx11::string clientNodeType = nextTree["node_type"].GetString();
        if (clientNodeType == BTCName::ActionNode) {
            std::__cxx11::string nodeAction = aiTreeDoc["node_action"].GetString();
            clientNode = CreateActionNode(nodeAction, nextTree);
        } else if (clientNodeType == BTCName::ControlNode) {
            std::string nodeAction = aiTreeDoc["node_action"].GetString();
            clientNode = CreateControlNode(nodeAction, nextTree);
        }
        node->PushChildNode(new BevChildNode(clientNode));
    }
    return node;
}

void BTCFactory::LoadActionNodeResource(BehaviorNode *node, const Value &aiTreeJson) {
    std::__cxx11::string nodeResource = aiTreeJson["node_resource"].GetString();
    JUDGE_RETURN(!nodeResource.empty(), ;);
    dynamic_cast<AIIMBaseAction*>(node)->LoadTmplImage(nodeResource);
}

void BTCFactory::LoadActionNodeResource(BehaviorNode *node, const Document& aiTreeDoc) {
    std::__cxx11::string nodeResource = aiTreeDoc["node_resource"].GetString();
    JUDGE_RETURN(!nodeResource.empty(), ;);
    dynamic_cast<AIIMBaseAction*>(node)->LoadTmplImage(nodeResource);
}

void BTCFactory::LoadConditionNode(BehaviorNode *node, const Value &aiTreeJson) {
    std::__cxx11::string extPreCond = aiTreeJson["ext_precond"].GetString();
    JUDGE_RETURN(!extPreCond.empty(), ;);
    ConditionBase* conditionNode = nullptr;
    NEW_CONDITION_NODE(BTCName::ConditionAppRunning, AIIMAppRunning);
    NEW_CONDITION_NODE(BTCName::ConditionOnObjScreen, AIIMOnObjScreenUI);
    JUDGE_RETURN(conditionNode != nullptr, ;);
    node->SetPrecondition(conditionNode);

    JUDGE_RETURN(aiTreeJson.HasMember("ext_precond_resource"), ;);
    std::__cxx11::string extPreCondResource = aiTreeJson["ext_precond_resource"].GetString();
    JUDGE_RETURN(!extPreCondResource.empty(), ;);
    dynamic_cast<AIIMConditionBase*>(conditionNode)->LoadTmplImage(extPreCondResource);
}

void BTCFactory::LoadConditionNode(BehaviorNode *node, const Document& aiTreeDoc) {
    std::__cxx11::string extPreCond = aiTreeDoc["ext_precond"].GetString();
    JUDGE_RETURN(!extPreCond.empty(), ;);
    ConditionBase* conditionNode = nullptr;
    NEW_CONDITION_NODE(BTCName::ConditionAppRunning, AIIMAppRunning);
    NEW_CONDITION_NODE(BTCName::ConditionOnObjScreen, AIIMOnObjScreenUI);
    JUDGE_RETURN(conditionNode != nullptr, ;);
    node->SetPrecondition(conditionNode);

    JUDGE_RETURN(aiTreeDoc.HasMember("ext_precond_resource"), ;);
    std::__cxx11::string extPreCondResource = aiTreeDoc["ext_precond_resource"].GetString();
    JUDGE_RETURN(!extPreCondResource.empty(), ;);
    dynamic_cast<AIIMConditionBase*>(conditionNode)->LoadTmplImage(extPreCondResource);
}

void BTCFactory::PrintfRootNode(BehaviorNode *node) {
    printf("=======================RootNode=======================\n");
    printf("RootNode name: %s\n", node->GetFieldName().c_str());
    BevChildNodeVec &childList = node->GetChildNodeList();
    if (node->GetPrecondition() != nullptr) {
        printf("RootNode condition : %s\n", node->GetPrecondition()->GetFieldName().c_str());
    }
    PrintfChildNode(childList);
}

void BTCFactory::PrintfChildNode(BevChildNodeVec &childNodeList) {
    JUDGE_RETURN(!childNodeList.empty(), ;);
    printf("=======================ChildNode=======================\n");
    for (auto item : childNodeList) {
        printf("ChildNode name: %s\n", item->m_pNode->GetFieldName().c_str());
        if (item->m_pNode->GetPrecondition() != nullptr) {
            printf("ChildNode condition name: %s\n", item->m_pNode->GetPrecondition()->GetFieldName().c_str());
        }
        PrintfChildNode(item->m_pNode->GetChildNodeList());
    }
}
