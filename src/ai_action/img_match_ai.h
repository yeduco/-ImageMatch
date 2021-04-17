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

namespace image_match{
    class ImageMatchAI{
    public:
        ImageMatchAI();
        ~ImageMatchAI() = default;
        void init();
        void SetTmplImage(const std::string& img_path);

        bool VerifyIsMatchRegion();

        void ExecuteMouseClick();

        cv::Mat& GetTmplImage();

        void SetAiTree(behavior::BehaviorNode* aiTree);

        void CaptureCurrentWindow();

        void MatchImagePos(int minHessian = 800);

        static void DetectAndComputeKeyPoint(cv::Ptr<cv::FeatureDetector> &detector,
                                             cv::Ptr<cv::DescriptorExtractor> &descriptor,
                                             cv::Mat &img1,std::vector<cv::KeyPoint> &outputKeyPoint1,
                                             cv::Mat &img2, std::vector<cv::KeyPoint> &outputKeyPoint2,
                                             cv::Mat &outputMat1, cv::Mat &outputMat2);

        static void MatchImage(cv::Mat &img1, std::vector<cv::KeyPoint>& keyPoint1,
                               cv::Mat &img2, std::vector<cv::KeyPoint>& keyPoint2,
                               cv::Mat &inputImg1Des, cv::Mat &inputImg2Des,
                               cv::Mat &outputImg, std::vector<cv::DMatch> &outputMatches,
                               std::vector<cv::DMatch> &outputGoodMatches);

        void test();

    private:
        behavior::BehaviorNode* m_aiTree;
        cv::Mat m_tmplImage;
        cv::Mat m_searchImage;
        HANDLE m_hProcess;
        HWND m_hMainHwnd;
        HWND m_hClientHwnd;


    };
}