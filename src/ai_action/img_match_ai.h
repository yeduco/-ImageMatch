//
// Created by iWong on 27/3/2021.
//

#ifndef BEHAVIORTREE_IMG_MATCH_AI_H
#define BEHAVIORTREE_IMG_MATCH_AI_H

#include <opencv2/opencv.hpp>
#include "string"
#include "windows.h"
#include "behavior/behavior_tree.h"
#include "public/tools.h"

class ImageMatchAI {
public:
    ImageMatchAI();

    ~ImageMatchAI() = default;

    bool init();

    HWND &GetMainHwnd();

    HWND &GetClientHwnd();

public:
    void ExecuteMouseClick(POINT point);

    void SetAiTree(behavior::BehaviorNode *aiTree);

    cv::Mat CreateMat();

    int ExecuteAiTree();

    void HookProcessMsg();

private:
    behavior::BehaviorNode *m_aiTree;
    HWND m_hMainHwnd;
    HWND m_hClientHwnd;
};
#endif //BEHAVIORTREE_IMG_MATCH_AI_H
