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
        //this->m_tmplImage = cv::imread(R"(H:\-ImageMatch\src\t.jpg)", cv::IMREAD_ANYCOLOR);
        this->m_tmplImage = cv::imread(imgPath, cv::IMREAD_GRAYSCALE);
    }


    HWND &ImageMatchAI::GetClientHwnd() {
        return this->m_hClientHwnd;
    }

    HWND &ImageMatchAI::GetMainHwnd() {
        return this->m_hMainHwnd;
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
//        printf("(%d, %d)\n", width, height);
        HDC hSrcDC = GetDC(this->m_hClientHwnd);
        HDC hMemDC = CreateCompatibleDC(hSrcDC);
        HBITMAP hMemBMP = CreateCompatibleBitmap(hSrcDC, width, height);
        static_cast<HBITMAP>(SelectObject(hMemDC, hMemBMP));
        BitBlt(hMemDC, 0, 0, width, height, hSrcDC, 0, 0, SRCCOPY | CAPTUREBLT);
        GetBitmapBits(hMemBMP, bmpSize, this->m_searchImage.data);
        DeleteObject(hMemBMP);
        DeleteDC(hMemDC);
        ReleaseDC(this->m_hClientHwnd, hSrcDC);
    }

    cv::Mat &ImageMatchAI::GetSearchImage() {
        return this->m_searchImage;
    }
}