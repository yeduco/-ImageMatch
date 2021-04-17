//
// Created by iWong on 12/4/2021.
//

#include <iostream>
#include <ai_action/img_match_ai.h>

int main(){
    std::cout << "hello" << std::endl;
    image_match::ImageMatchAI ai;
    ai.init();
    ai.SetTmplImage(R"(H:\-ImageMatch\src\t.jpg)");
//    ai.ExecuteMouseClick();
    ai.CaptureCurrentWindow();
    ai.MatchImagePos(100);
//    ai.test();
    return 0;
}