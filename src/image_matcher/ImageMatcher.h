//
// Created by iWong on 20/4/2021.
//

#ifndef _IMAGEMATCH_IMAGEMATCHER_H
#define _IMAGEMATCH_IMAGEMATCHER_H
#include <opencv2/opencv.hpp>
#include "string"
#include "windows.h"
#include "public/tools.h"


class ImageMatcher {
public:
    enum EMatcherType{
        E_FEATURE_MATCHER = 1,
        E_TEMPLATE_MATCHER = 2
    };

    ImageMatcher() = default;
    ~ImageMatcher() = default;

    static std::tuple<bool, int, int, cv::Mat> Match(cv::Mat& tmplImage, cv::Mat& mainImage, int type = E_FEATURE_MATCHER, int matchType = cv::TM_CCOEFF_NORMED,int minHessian = 400);


    static std::tuple<bool, int, int, cv::Mat> FeatureMatcher(cv::Mat& tmplImage, cv::Mat& mainImage, int minHessian = 400);

    static std::tuple<bool, int, int, cv::Mat> TemplateMatcher(cv::Mat& tmplImage, cv::Mat& mainImage, int matchType);

    static void DetectAndComputeKeyPoint(cv::Ptr<cv::FeatureDetector> &detector,
                                         cv::Ptr<cv::DescriptorExtractor> &descriptor,
                                         cv::Mat &img1, std::vector<cv::KeyPoint> &outputKeyPoint1,
                                         cv::Mat &img2, std::vector<cv::KeyPoint> &outputKeyPoint2,
                                         cv::Mat &outputMat1, cv::Mat &outputMat2);

    static void MatchImage(cv::Mat &img1, std::vector<cv::KeyPoint> &keyPoint1,
                           cv::Mat &img2, std::vector<cv::KeyPoint> &keyPoint2,
                           cv::Mat &inputImg1Des, cv::Mat &inputImg2Des,
                           cv::Mat &outputImg, std::vector<cv::DMatch> &outputMatches,
                           std::vector<cv::DMatch> &outputGoodMatches);

    static void drawLine(cv::Mat &tmplImg, cv::Mat &mainImage, cv::Mat &matchesImage, std::vector<cv::Point2f> &Point2fVec);

    static cv::Point CenterPos(cv::Point &leftTopPos, cv::Point &rightBottomPos);

    static cv::Point CenterPos(cv::Point2f &leftTopPos, cv::Point2f &rightBottomPos);

    static bool CaptureScreen(HWND &hwnd, cv::Mat& output);
};


#endif //_IMAGEMATCH_IMAGEMATCHER_H
