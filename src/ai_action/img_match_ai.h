//
// Created by iWong on 27/3/2021.
//

#ifndef BEHAVIORTREE_IMG_MATCH_AI_H
#define BEHAVIORTREE_IMG_MATCH_AI_H

#endif //BEHAVIORTREE_IMG_MATCH_AI_H

#include <opencv2/opencv.hpp>
#include "string"
#include "windows.h"
#include "behavior/behavior_tree.h"

namespace image_match {
    class ImageMatchAI {
    public:
        ImageMatchAI();

        ~ImageMatchAI() = default;

        void init();

        void SetTmplImage(const std::string &img_path);

        HWND& GetMainHwnd();
        HWND& GetClientHwnd();
    public:
        void ExecuteMouseClick(POINT point);

        cv::Mat &GetTmplImage();
        cv::Mat &GetSearchImage();

        void SetAiTree(behavior::BehaviorNode *aiTree);

        void CaptureCurrentWindow();

    private:
        behavior::BehaviorNode *m_aiTree;
        cv::Mat m_tmplImage;
        cv::Mat m_searchImage;
        HWND m_hMainHwnd;
        HWND m_hClientHwnd;


    };
}