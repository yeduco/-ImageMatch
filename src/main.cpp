//
// Created by iWong on 12/4/2021.
//

#include <iostream>
#include <ai_action/img_match_ai.h>
#include <image_matcher/ImageMatcher.h>
#include "include.h"
#include "public/configure.h"

int main(){
//    std::cout << "hello" << std::endl;
//    image_match::ImageMatchAI ai;
//    ai.init();
//    ai.SetTmplImage(R"(H:\-ImageMatch\src\t.jpg)");
//    ai.CaptureCurrentWindow();
//    std::tuple<bool, int, int, cv::Mat> result = ImageMatcher::Match(ai.GetTmplImage(), ai.GetSearchImage(), ImageMatcher::E_FEATURE_MATCHER);
//    bool isMatch = std::get<0>(result);
//    int x = std::get<1>(result);
//    int y = std::get<2>(result);
//    cv::Mat showImage = std::get<3>(result);
//    cv::imshow("title",showImage );
//    POINT point;
//    point.x = x;
//    point.y = y;
//    cv::waitKey(0);
//    if (isMatch){
//        ai.ExecuteMouseClick(point);
//        return 0;
//    }
//    char path[256];
//    GetCurrentDirectory(256, path);
//
//    FILE* pFile = fopen("..\\src\\birth.json", "rb");
//    if(pFile != nullptr){
//        char readBuffer[65535];
//        rapidjson::FileReadStream inputStream(pFile, readBuffer, sizeof(readBuffer));
//        rapidjson::Document d;
//        d.ParseStream(inputStream);
//        fclose(pFile);
//        if(d.HasMember("1")){
//            printf("%s", d["1"]["name"].GetString());
//            printf("have");
//        }
////        printf("%s", d["1"]["name"].GetString());
//        return 0;
//    }
//    ai.test();
    return 0;
}