//
// Created by iWong on 27/3/2021.
//

#include "img_match_ai.h"

ImageMatchAI::ImageMatchAI() {
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

cv::Mat &ImageMatchAI::GetTmplImage() {
    return this->m_tmplImage;
}

void ImageMatchAI::SetTmplImage(const std::string &imgPath) {
    //this->m_tmplImage = cv::imread(R"(H:\-ImageMatch\src\t.jpg)", cv::IMREAD_ANYCOLOR);
    this->m_tmplImage = cv::imread(imgPath, cv::IMREAD_GRAYSCALE);
}


HWND &ImageMatchAI::GetClientHwnd() {
    return this->m_hClientHwnd;
}

HWND &ImageMatchAI::GetMainHwnd() {
    return this->m_hMainHwnd;
}

void ImageMatchAI::ExecuteMouseClick(POINT point) {
    ClientToScreen(this->m_hClientHwnd, &point);
    SetCursorPos(point.x, point.y);
    printf("ClientToScreen x:%d, y:%d\n", point.x, point.y);
    SendMessage(this->m_hClientHwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(point.x, point.y));
    SendMessage(this->m_hClientHwnd, WM_LBUTTONUP, 0, MAKELPARAM(point.x, point.y));
}

void ImageMatchAI::SetAiTree(behavior::BehaviorNode *aiTree) {

}

cv::Mat &ImageMatchAI::GetSearchImage() {
    return this->m_searchImage;
}

cv::Mat ImageMatchAI::CreateMat() {
    int width = 0;
    int height = 0;
    GetWindowWidthHeight(this->m_hClientHwnd, width, height);
    return cv::Mat(height, width, CV_8UC4);
}