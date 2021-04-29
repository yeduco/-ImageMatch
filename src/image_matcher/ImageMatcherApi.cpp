//
// Created by iWong on 20/4/2021.
//

#include "ImageMatcherApi.h"
std::tuple<bool, int, int, cv::Mat> ImageMatcherApi::Match(cv::Mat& tmplImage, cv::Mat& mainImage, int type, int matchType, int minHessian) {
    switch(type){
        case E_FEATURE_MATCHER:
            return FeatureMatcher(tmplImage, mainImage, minHessian);
        case E_TEMPLATE_MATCHER:
            return TemplateMatcher(tmplImage, mainImage, matchType);
        default:
            return std::tuple<bool, int, int, cv::Mat>(false, 0, 0, cv::Mat());
    }
}


std::tuple<bool, int, int, cv::Mat> ImageMatcherApi::FeatureMatcher(cv::Mat &tmplImage, cv::Mat &mainImage, int minHessian) {
    // SURF特征点检测
    cv::Ptr<cv::FeatureDetector> detector = cv::SIFT::create(minHessian);
    std::vector<cv::KeyPoint> searchKeyPoint;
    std::vector<cv::KeyPoint> tmplKeyPoint;
    std::vector<cv::DMatch> matches;  //存放匹配结果
    std::vector<cv::DMatch> goodMatches;  //选出最好的匹配结果
    std::tuple<bool, int, int, cv::Mat> result(false, 0, 0, cv::Mat());
    cv::Mat tmplDescriptor, searchDescriptor, matchesImage;
    DetectAndComputeKeyPoint(detector, detector, tmplImage,
                             tmplKeyPoint, mainImage, searchKeyPoint,
                             tmplDescriptor, searchDescriptor);

    MatchImage(tmplImage, tmplKeyPoint, mainImage, searchKeyPoint,
               tmplDescriptor, searchDescriptor, matchesImage, matches, goodMatches);

    std::vector<cv::Point2f> tmplPoint;
    std::vector<cv::Point2f> searchPoint;

    for(auto & info : matches){
        tmplPoint.push_back(tmplKeyPoint[info.queryIdx].pt);
        searchPoint.push_back(searchKeyPoint[info.trainIdx].pt);
    }
    std::vector<u_char> inLinersMask;

    cv::Mat h = cv::findHomography(tmplPoint, searchPoint, cv::RANSAC, 3, inLinersMask);

    std::vector<cv::DMatch> inLiners;
    for(int i = 0; i < inLinersMask.size(); i++){
        if(inLinersMask[i])
        {
            inLiners.push_back(matches[i]);
        }
    }
    JUDGE_RETURN(inLiners.size() >= 4, result);
    matches.swap(inLiners);
    cv::drawMatches(tmplImage, tmplKeyPoint,mainImage, searchKeyPoint,
                    matches, matchesImage, cv::Scalar::all(-1), CV_RGB(0, 0, 255),
                    std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

    std::vector<cv::Point2f> tmplCorner(4);
    std::vector<cv::Point2f> searchCorner(4);
    tmplCorner[0] = cv::Point(0,0);
    tmplCorner[1] = cv::Point(tmplImage.cols, 0);
    tmplCorner[2] = cv::Point(tmplImage.cols, tmplImage.rows);
    tmplCorner[3] = cv::Point(0, tmplImage.rows);

    cv::perspectiveTransform(tmplCorner, searchCorner, h);
    drawLine(tmplImage, mainImage, matchesImage, searchCorner);
    JUDGE_RETURN(IsIrregularRectangle(searchCorner), result);
    int matchRatio = int(matches.size() * 0.85);
    int matchNumber = 0;
    for(auto & i : matches){
        cv::Point2f target = searchKeyPoint[i.trainIdx].pt;
        if(IsInIrregularRectangle(searchCorner, target))
            matchNumber++;
    }
    JUDGE_RETURN(matchNumber >= matchRatio, result);
    cv::Point centerPos = CenterPos(searchCorner[0],searchCorner[2]);
    std::get<0>(result) = true;
    std::get<1>(result) = centerPos.x;
    std::get<2>(result) = centerPos.y;
    mainImage.copyTo(std::get<3>(result));
    return result;
}


std::tuple<bool, int, int, cv::Mat> ImageMatcherApi::TemplateMatcher(cv::Mat &tmplImage, cv::Mat &mainImage, int matchType) {
    std::tuple<bool, int, int, cv::Mat> result(false, 0, 0, cv::Mat());
    cv::Mat resultImage;
    int result_cols = mainImage.cols - tmplImage.cols + 1;
    int result_rows = mainImage.rows - tmplImage.rows + 1;
    if(tmplImage.channels() != 1)
        cv::cvtColor(tmplImage, tmplImage, cv::COLOR_RGB2GRAY);
    if(mainImage.channels() != 1)
        cv::cvtColor(mainImage, mainImage, cv::COLOR_RGB2GRAY);
    resultImage.create(result_cols, result_rows, CV_32FC1);

    cv::matchTemplate(mainImage, tmplImage, resultImage, matchType);
//    cv::normalize(resultImage, resultImage, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    double minVal, maxVal;
    cv::Point minLoc, maxLoc;
    cv::Point matchLoc;
    minMaxLoc(resultImage, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

    JUDGE_RETURN(maxVal > 0.8, result);
    if(matchType == cv::TM_SQDIFF || matchType == cv::TM_SQDIFF_NORMED)
        matchLoc = minLoc;
    else
        matchLoc = maxLoc;
    cv::Point rightBottomPos(maxLoc.x + tmplImage.cols, maxLoc.y + tmplImage.rows);
    int x = int((matchLoc.x + rightBottomPos.x) / 2);
    int y = int((matchLoc.y + rightBottomPos.y) / 2);
    cv::Point centerPos = CenterPos(matchLoc, rightBottomPos);
    cv::rectangle(mainImage, matchLoc, cv::Point(rightBottomPos.x, rightBottomPos.y),
                  cv::Scalar(0, 0, 245), 2, 8, 0);
    circle(mainImage, cv::Point(x, y), 6, cv::Scalar(0, 0, 255), 8);

//    cv::imshow("title", mainImage);
//    cv::waitKey(0);
    std::get<0>(result) = true;
    std::get<1>(result) = centerPos.x;
    std::get<2>(result) = centerPos.y;
    mainImage.copyTo(std::get<3>(result));
    return result;
}

void ImageMatcherApi::DetectAndComputeKeyPoint(cv::Ptr<cv::FeatureDetector> &detector,
                                            cv::Ptr<cv::DescriptorExtractor> &descriptor,
                                            cv::Mat &img1,std::vector<cv::KeyPoint> &outputKeyPoint1,
                                            cv::Mat &img2, std::vector<cv::KeyPoint> &outputKeyPoint2,
                                            cv::Mat &outputMat1, cv::Mat &outputMat2) {
    detector->detect(img1, outputKeyPoint1);
    detector->detect(img2, outputKeyPoint2);
    descriptor->compute(img1, outputKeyPoint1, outputMat1);
    descriptor->compute(img2, outputKeyPoint2, outputMat2);
}

void ImageMatcherApi::MatchImage(cv::Mat &img1, std::vector<cv::KeyPoint>& keyPoint1,
                              cv::Mat &img2, std::vector<cv::KeyPoint>& keyPoint2,
                              cv::Mat &inputImg1Des, cv::Mat &inputImg2Des,
                              cv::Mat &outputImg, std::vector<cv::DMatch> &outputMatches,
                              std::vector<cv::DMatch> &outputGoodMatches) {
//        cv::BFMatcher matcher(cv::NORM_L2, true);
    cv::FlannBasedMatcher matcher;
    matcher.match(inputImg1Des, inputImg2Des, outputMatches);
//        double minDistance = 1000;  //反向逼近
//        double maxDistance = 0;

//        std::sort(outputMatches.begin(), outputMatches.end());
//        int ptsPairs = std::min(50, int(outputMatches.size() * 0.15));
//
//        for(int i = 0; i < ptsPairs; i++){
//            outputGoodMatches.push_back(outputMatches[i]);
//        }
}

void ImageMatcherApi::drawLine(cv::Mat &tmplImg, cv::Mat &mainImage, cv::Mat &matchesImage, std::vector<cv::Point2f> &Point2fVec) {
//    line(matchesImage, Point2fVec[0] + cv::Point2f(tmplImg.cols, 0), Point2fVec[1] + cv::Point2f(tmplImg.cols, 0), cv::Scalar(0, 0, 255), 2, 8, 0);
//    line(matchesImage, Point2fVec[1] + cv::Point2f(tmplImg.cols, 0), Point2fVec[2] + cv::Point2f(tmplImg.cols, 0), cv::Scalar(0, 0, 255), 2, 8, 0);
//    line(matchesImage, Point2fVec[2] + cv::Point2f(tmplImg.cols, 0), Point2fVec[3] + cv::Point2f(tmplImg.cols, 0), cv::Scalar(0, 0, 255), 2, 8, 0);
//    line(matchesImage, Point2fVec[3] + cv::Point2f(tmplImg.cols, 0), Point2fVec[0] + cv::Point2f(tmplImg.cols, 0), cv::Scalar(0, 0, 255), 2, 8, 0);
////
//    imshow("FLANN Image", matchesImage);

    line(mainImage, Point2fVec[0], Point2fVec[1], cv::Scalar(0, 0, 255), 2, 8, 0);
    line(mainImage, Point2fVec[1], Point2fVec[2], cv::Scalar(0, 0, 255), 2, 8, 0);
    line(mainImage, Point2fVec[2], Point2fVec[3], cv::Scalar(0, 0, 255), 2, 8, 0);
    line(mainImage, Point2fVec[3], Point2fVec[0], cv::Scalar(0, 0, 255), 2, 8, 0);
//
    int x = int(((Point2fVec[0].x + Point2fVec[2].x) / 2));
    int y = int(((Point2fVec[0].y + Point2fVec[2].y) / 2));
    circle(mainImage, cv::Point(x, y), 6, cv::Scalar(0, 255, 0), 8);
//    cv::imshow("title", matchesImage);
//    cv::waitKey(0);
}

cv::Point ImageMatcherApi::CenterPos(cv::Point &leftTopPos, cv::Point &rightBottomPos) {
    double dpiSaleFactor = GetWindowDpiScaleFactor();
    int x = int((leftTopPos.x + rightBottomPos.x) / 2 / dpiSaleFactor);
    int y = int((leftTopPos.y + rightBottomPos.y) / 2 / dpiSaleFactor);
    return {x,y};
}

cv::Point ImageMatcherApi::CenterPos(cv::Point2f &leftTopPos, cv::Point2f &rightBottomPos) {
    double dpiSaleFactor = GetWindowDpiScaleFactor();
    int x = int(((leftTopPos.x + rightBottomPos.x) / 2) / dpiSaleFactor);
    int y = int(((leftTopPos.y + rightBottomPos.y) / 2) / dpiSaleFactor);
    return {x,y};
}

bool ImageMatcherApi::CaptureScreen(HWND &hwnd, cv::Mat &output) {
    JUDGE_RETURN(hwnd != nullptr, false);
    int width = 0;
    int height = 0;
    GetWindowWidthHeight(hwnd, width, height);
    int bmpSize = width * height * 4;
    HDC hSrcDC = GetDC(hwnd);
    HDC hMemDC = CreateCompatibleDC(hSrcDC);
    HBITMAP hMemBMP = CreateCompatibleBitmap(hSrcDC, width, height);
    static_cast<HBITMAP>(SelectObject(hMemDC, hMemBMP));
    BitBlt(hMemDC, 0, 0, width, height, hSrcDC, 0, 0, SRCCOPY | CAPTUREBLT);
    GetBitmapBits(hMemBMP, bmpSize, output.data);
    DeleteObject(hMemBMP);
    DeleteDC(hMemDC);
    ReleaseDC(hwnd, hSrcDC);
    return true;
}
