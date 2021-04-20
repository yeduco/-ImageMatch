//
// Created by iWong on 12/4/2021.
//

#include <iostream>
#include <ai_action/img_match_ai.h>
#include <image_matcher/ImageMatcher.h>

int main(){
    std::cout << "hello" << std::endl;
    image_match::ImageMatchAI ai;
    ai.init();
    ai.SetTmplImage(R"(H:\-ImageMatch\src\t.jpg)");
//    ai.ExecuteMouseClick();
    ai.CaptureCurrentWindow();
    std::tuple<bool, int, int, cv::Mat> result = ImageMatcher::Match(ai.GetTmplImage(), ai.GetSearchImage(), ImageMatcher::E_FEATURE_MATCHER);
    bool isMatch = std::get<0>(result);
    int x = std::get<1>(result);
    int y = std::get<2>(result);
    cv::Mat showImage = std::get<3>(result);
    cv::imshow("title",showImage );
    HWND& main = ai.GetMainHwnd();
    HWND& client = ai.GetClientHwnd();

    POINT ClientPos;
    ClientPos.x = x;
    ClientPos.y = y;

    ClientToScreen(client, &ClientPos);
//    SetCursorPos(ClientPos.x, ClientPos.y);
    cv::waitKey(0);
    if (isMatch){
        printf("match pos(%d, %d)", x, y);
        printf("client pos(%d, %d)", ClientPos.x, ClientPos.y);
        return 0;
    }

    printf("not match");

//    ai.test();
    return 0;
}