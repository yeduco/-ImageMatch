//
// Created by iWong on 27/3/2021.
//

#include "img_match_ai.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "tool/tools.h"
#include "vector"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"


namespace image_match{

    ImageMatchAI::ImageMatchAI() {
        this->m_hProcess = nullptr;
        this->m_aiTree = nullptr;
        this->m_hMainHwnd = nullptr;
        this->m_hClientHwnd = nullptr;
    }

    void ImageMatchAI::init() {
        this->m_hMainHwnd = GetWindowHwnd("LDPlayerMainFrame");
//        this->m_hHwnd = GetWindowHwnd("LDPlayerMainFrame");
        this->m_hClientHwnd = FindWindowEx(this->m_hMainHwnd, nullptr, "RenderWindow", nullptr);
        int width = 0;
        int height = 0;
        GetWindowWidthHeight(this->m_hClientHwnd, width, height);
//        this->m_searchImage.create(height, width, CV_8UC4);
        this->m_searchImage.create(height, width, CV_8UC4);
        SetWindowPos(this->m_hMainHwnd, HWND_TOP,
                     0, 0, 0, 0, SWP_NOSIZE | SWP_NOCOPYBITS);
    }

    cv::Mat& ImageMatchAI::GetTmplImage() {
        return this->m_tmplImage;
    }

    void ImageMatchAI::SetTmplImage(const std::string &imgPath) {
        this->m_tmplImage = cv::imread(imgPath, cv::IMREAD_GRAYSCALE);
    }

    bool ImageMatchAI::VerifyIsMatchRegion() {
        cv::Mat search;
//        WindowCapture()


        this->m_tmplImage;
        return false;
    }

    void ImageMatchAI::ExecuteMouseClick() {
        RECT rc;
        int width = 0;
        int height = 0;
        GetWindowWidthHeight(this->m_hClientHwnd, width, height);
        GetClientRect(this->m_hClientHwnd, &rc);
        printf("GetClientRect width:%d, height:%d\n", rc.right, rc.bottom);
        GetWindowRect(this->m_hClientHwnd, &rc);
        printf("GetWindowRect width:%d, height:%d\n", rc.right - rc.left, rc.bottom - rc.top);
        POINT pos;
        pos.x = rc.right / 2;
        pos.y = rc.bottom / 2;
//        ScreenToClient(this->m_hClientHwnd, &pos);
        ClientToScreen(this->m_hClientHwnd, &pos);
        printf("ScreenToClient x:%d, y:%d\n",pos.x,pos.y);
        SetCursorPos(pos.x, pos.y);
//        ClientToScreen(this->m_hMainHwnd, &pos);
//        printf("ClientToScreen x:%d, y:%d\n",pos.x,pos.y);
//        SendMessage(this->m_hClientHwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(279, 158));
//        SendMessage(this->m_hClientHwnd, WM_LBUTTONUP, 0, MAKELPARAM(279, 158));
    }

    void ImageMatchAI::SetAiTree(behavior::BehaviorNode *aiTree) {

    }

    void ImageMatchAI::CaptureCurrentWindow() {
        JUDGE_RETURN(this->m_hClientHwnd != nullptr, ;);
        int width = 0;
        int height = 0;
        GetWindowWidthHeight(this->m_hClientHwnd, width, height);
        int bmpSize = width * height * 4;
        printf("(%d, %d)\n", width, height);
        HDC hSrcDC = GetDC(this->m_hClientHwnd);
        HDC hMemDC = CreateCompatibleDC(hSrcDC);
        HBITMAP hMemBMP = CreateCompatibleBitmap(hSrcDC, width, height);
        static_cast<HBITMAP>(SelectObject(hMemDC, hMemBMP));
        BitBlt(hMemDC, 0, 0, width, height, hSrcDC, 0, 0, SRCCOPY | CAPTUREBLT);
        GetBitmapBits(hMemBMP, bmpSize, this->m_searchImage.data);
        DeleteObject(hMemBMP);
        DeleteDC(hMemDC);
        ReleaseDC(this->m_hClientHwnd, hSrcDC);
//        cv::imshow("title", this->m_searchImage);
//        cv::waitKey(0);
        int centerX = width / 2;
        int centerY = height / 2;
//        SetCursorPos(centerX, centerY);
//        cv::cvtColor(this->m_searchImage, this->m_searchImage,cv::COLOR_BGRA2RGB);
//        cv::cvtColor(this->m_searchImage, this->m_searchImage,cv::COLOR_GRAY2RGB);
//        SetWindowPos(this->m_hHwnd, HWND_TOPMOST, centerX, centerY, 0, 0, SWP_NOSIZE | SWP_NOCOPYBITS);

    }

    void ImageMatchAI::MatchImagePos(int minHessian) {
        this->m_tmplImage = cv::imread(R"(H:\-ImageMatch\src\t.jpg)", cv::IMREAD_ANYCOLOR);
        cv::Mat& tmplImg = this->m_tmplImage;

        cv::Mat searchImg = this->m_searchImage;
//        this->m_searchImage.convertTo(searchImg, CV_32F);
//        cv::imshow("title", searchImg);
        // SURF特征点检测
        cv::Ptr<cv::FeatureDetector> detector1 = cv::SIFT::create(800);
        cv::Ptr<cv::FeatureDetector> detector = cv::xfeatures2d::SURF::create(minHessian);
//        cv::Ptr<cv::DescriptorExtractor> beblidDescriptor = cv::xfeatures2d::BEBLID::create(0.75, cv::xfeatures2d::BEBLID::SIZE_256_BITS);
//        cv::Ptr<cv::FeatureDetector> orbDetector = cv::ORB::create(400);
        std::vector<cv::KeyPoint> searchKeyPoint;
        std::vector<cv::KeyPoint> tmplKeyPoint;
        std::vector<cv::DMatch> matches;  //存放匹配结果
        std::vector<cv::DMatch> goodMatches;  //选出最好的匹配结果

        cv::Mat tmplDescriptor, searchDescriptor, matchesImage;
        DetectAndComputeKeyPoint(detector1, detector1, tmplImg,
                                 tmplKeyPoint, searchImg, searchKeyPoint,
                                 tmplDescriptor, searchDescriptor);

        MatchImage(tmplImg, tmplKeyPoint, searchImg, searchKeyPoint,
                   tmplDescriptor, searchDescriptor, matchesImage, matches, goodMatches);



        std::vector<cv::Point2f> tmplPoint;
        std::vector<cv::Point2f> searchPoint;

        for(size_t i = 0; i < matches.size(); i++){
            tmplPoint.push_back(tmplKeyPoint[matches[i].queryIdx].pt);
            searchPoint.push_back(searchKeyPoint[matches[i].trainIdx].pt);
        }
        std::vector<u_char> inLinersMask;

        cv::Mat h = cv::findHomography(tmplPoint, searchPoint, cv::RANSAC, 3, inLinersMask);

        std::vector<cv::DMatch> inLiners;
        for(int i = 0; i < inLinersMask.size(); i++){
            if(inLinersMask[i])
            {
//                printf("matches(trainIdx:%f, queryIdx:%f) Distance:%f\n", matches[i].trainIdx, matches[i].queryIdx, matches[i].distance);
                inLiners.push_back(matches[i]);
            }
        }
        matches.swap(inLiners);
        printf("real matches size :%d\n", matches.size());
        printf("real inLiners size :%d\n", inLiners.size());
        cv::drawMatches(tmplImg, tmplKeyPoint,searchImg, searchKeyPoint,
                        matches, matchesImage, cv::Scalar::all(-1), CV_RGB(0, 0, 255),
                        std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
//        cv::Mat h = cv::findHomography(searchPoint, tmplPoint, cv::RANSAC);

        std::vector<cv::Point2f> tmplCorner(4);
        std::vector<cv::Point2f> searchCorner(4);
        tmplCorner[0] = cv::Point(0,0);
        tmplCorner[1] = cv::Point(this->m_tmplImage.cols, 0);
        tmplCorner[2] = cv::Point(this->m_tmplImage.cols, this->m_tmplImage.rows);
        tmplCorner[3] = cv::Point(0, this->m_tmplImage.rows);

        cv::perspectiveTransform(tmplCorner, searchCorner, h);
        POINT pos;
        pos.x = searchCorner[0].x;
        pos.y = searchCorner[0].y;
        ClientToScreen(this->m_hClientHwnd, &pos);
        SetCursorPos(pos.x, pos.y);
//        printf("width:%d height:%d\n", tmplImg.cols, tmplImg.rows);
        printf("point 1 x:%f y:%f\n", searchCorner[0].x, searchCorner[0].y);
        printf("point 2 x:%f y:%f\n", searchCorner[1].x, searchCorner[1].y);
        printf("point 3 x:%f y:%f\n", searchCorner[2].x, searchCorner[2].y);
        printf("point 4 x:%f y:%f\n", searchCorner[3].x, searchCorner[3].y);

        if (IsIrregularRectangle(searchCorner))
            printf("this is irregular\n");
        else
            printf("this not's irregular\n");

        for(auto & i : matches){
            cv::Point2f target = searchKeyPoint[i.trainIdx].pt;
            if(IsInIrregularRectangle(searchCorner, target)){
                printf("target (%f, %f) is in rect!!\n", target.x, target.y);
            }
            else
            {
                printf("target (%f, %f) not's in rect!!\n", target.x, target.y);
            }
        }


//        double distance = sqrtf(powf((searchCorner[0].x - searchCorner[1].x),2) + powf((searchCorner[0].y - searchCorner[1].y),2));
//        printf("point1 to point2 dance %f\n", sqrtf(powf((searchCorner[0].x - searchCorner[1].x),2) + powf((searchCorner[0].y - searchCorner[1].y),2)));
//        printf("point2 to point3 dance %f\n", sqrtf(powf((searchCorner[1].x - searchCorner[2].x),2) + powf((searchCorner[1].y - searchCorner[2].y),2)));
//        printf("point3 to point4 dance %f\n", sqrtf(powf((searchCorner[2].x - searchCorner[3].x),2) + powf((searchCorner[2].y - searchCorner[3].y),2)));
//        printf("point4 to point1 dance %f\n", sqrtf(powf((searchCorner[3].x - searchCorner[0].x),2) + powf((searchCorner[3].y - searchCorner[0].y),2)));

        line(matchesImage, searchCorner[0] + cv::Point2f(this->m_tmplImage.cols, 0), searchCorner[1] + cv::Point2f(this->m_tmplImage.cols, 0), cv::Scalar(0, 0, 255), 2, 8, 0);
        line(matchesImage, searchCorner[1] + cv::Point2f(this->m_tmplImage.cols, 0), searchCorner[2] + cv::Point2f(this->m_tmplImage.cols, 0), cv::Scalar(0, 0, 255), 2, 8, 0);
        line(matchesImage, searchCorner[2] + cv::Point2f(this->m_tmplImage.cols, 0), searchCorner[3] + cv::Point2f(this->m_tmplImage.cols, 0), cv::Scalar(0, 0, 255), 2, 8, 0);
        line(matchesImage, searchCorner[3] + cv::Point2f(this->m_tmplImage.cols, 0), searchCorner[0] + cv::Point2f(this->m_tmplImage.cols, 0), cv::Scalar(0, 0, 255), 2, 8, 0);
//
        imshow("FLANN Image", matchesImage);

        line(this->m_searchImage, searchCorner[0], searchCorner[1], cv::Scalar(0, 0, 255), 2, 8, 0);
        line(this->m_searchImage, searchCorner[1], searchCorner[2], cv::Scalar(0, 0, 255), 2, 8, 0);
        line(this->m_searchImage, searchCorner[2], searchCorner[3], cv::Scalar(0, 0, 255), 2, 8, 0);
        line(this->m_searchImage, searchCorner[3], searchCorner[0], cv::Scalar(0, 0, 255), 2, 8, 0);
//
        cv::imshow("title", this->m_searchImage);
        cv::waitKey(0);
    }

    void ImageMatchAI::DetectAndComputeKeyPoint(cv::Ptr<cv::FeatureDetector> &detector,
                                      cv::Ptr<cv::DescriptorExtractor> &descriptor,
                                      cv::Mat &img1,std::vector<cv::KeyPoint> &outputKeyPoint1,
                                      cv::Mat &img2, std::vector<cv::KeyPoint> &outputKeyPoint2,
                                      cv::Mat &outputMat1, cv::Mat &outputMat2) {
        detector->detect(img1, outputKeyPoint1);
        detector->detect(img2, outputKeyPoint2);
        descriptor->compute(img1, outputKeyPoint1, outputMat1);
        descriptor->compute(img2, outputKeyPoint2, outputMat2);
    }

    void ImageMatchAI::MatchImage(cv::Mat &img1, std::vector<cv::KeyPoint>& keyPoint1,
                                  cv::Mat &img2, std::vector<cv::KeyPoint>& keyPoint2,
                                  cv::Mat &inputImg1Des, cv::Mat &inputImg2Des,
                                  cv::Mat &outputImg, std::vector<cv::DMatch> &outputMatches,
                                  std::vector<cv::DMatch> &outputGoodMatches) {
//        cv::BFMatcher matcher(cv::NORM_L2, true);
        cv::FlannBasedMatcher matcher;
        matcher.match(inputImg1Des, inputImg2Des, outputMatches);
        double minDistance = 1000;  //反向逼近
        double maxDistance = 0;

//        for(int i = 0; i < inputImg1Des.rows; i++){
//            double distance = outputMatches[i].distance;
//            if (distance > maxDistance) maxDistance = distance;
//            if (distance < minDistance) minDistance = distance;
//        }
//
//        for (int i = 0; i < inputImg1Des.rows; i++) {
//            double distance = outputMatches[i].distance;
//            if (distance < std::max(minDistance * 2, 0.02)) {
//                outputGoodMatches.push_back(outputMatches[i]);//距离小于范围的压入新的DMatch
//            }
//        }
        std::sort(outputMatches.begin(), outputMatches.end());
        int ptsPairs = std::min(50, int(outputMatches.size() * 0.15));

        for(int i = 0; i < ptsPairs; i++){
            outputGoodMatches.push_back(outputMatches[i]);
        }

        printf("maxDistance :%f\n", maxDistance);
        printf("minDistance :%f\n", minDistance);
        printf("goodMatches size :%d\n", outputGoodMatches.size());
        printf("tmplKeyPoint size :%d\n", keyPoint1.size());
        printf("matches size :%d\n", outputMatches.size());

//        cv::drawMatches(img1, keyPoint1,img2, keyPoint2,
//                        outputGoodMatches, outputImg, cv::Scalar::all(-1), CV_RGB(0, 0, 255),
//                        std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);
//        cv::drawMatches(img1, keyPoint1, img2, keyPoint2, outputMatches, outputImg);
    }
}