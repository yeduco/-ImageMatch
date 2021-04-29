//
// Created by iWong on 12/4/2021.
//

#include <iostream>
#include <ai_action/img_match_ai.h>
#include <image_matcher/ImageMatcherApi.h>
#include "include.h"
#include "public/configure.h"
#include "image_matcher/ImageMatcherApi.h"

int main(){
    CONFIG_INSTANCE->init();
    auto* ai = new ImageMatchAI;
    ai->init();
    ai->ExecuteAiTree();
//    cv::Mat mainImage = ai->CreateMat();
//    ai->CreateMat().copyTo(mainImage);
//    ImageMatcher::CaptureScreen(ai->GetClientHwnd(), mainImage);
////    cv::Mat mainImage = cv::imread(R"(H:\-ImageMatch\src\s.jpg)", cv::IMREAD_ANYCOLOR);
//    cv::Mat tmplImage = cv::imread(R"(H:\-ImageMatch\src\t.jpg)", cv::IMREAD_ANYCOLOR);
////
//    ImageMatcher::Match(tmplImage, mainImage);

    return 0;
}