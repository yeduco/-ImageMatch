//
// Created by iWong on 27/3/2021.
//

#include "img_match_ai.h"
#include "public/configure.h"
#include "btc_factory/BTCFactory.h"
#include "include.h"

ImageMatchAI::ImageMatchAI() {
    this->m_aiTree = nullptr;
    this->m_hMainHwnd = nullptr;
    this->m_hClientHwnd = nullptr;
}

bool ImageMatchAI::init() {
    rapidjson::Document &config = CONFIG_INSTANCE->GetBaseConfig();
    std::string appClassName = config["app_main_name"].GetString();
    std::string appChildName = config["app_child_name"].GetString();
    JUDGE_RETURN(!appClassName.empty(), false);
    if (config.HasMember("app_version")) {
        std::string version = config["app_version"].GetString();
        if (!version.empty()) {
            this->m_hMainHwnd = GetProcessHwndByClassNameAndVersion(appClassName, version);
            if (!appChildName.empty()) {
                this->m_hClientHwnd = FindWindowEx(this->m_hMainHwnd, nullptr, appChildName.c_str(), nullptr);
            } else {
                this->m_hMainHwnd = GetWindowHwnd(appClassName);
                if (!appChildName.empty()) {
                    this->m_hClientHwnd = FindWindowEx(this->m_hMainHwnd, nullptr, appChildName.c_str(), nullptr);
                }
            }
        }
    }
    int width = 0;
    int height = 0;
    GetWindowWidthHeight(this->m_hClientHwnd, width, height);
    SetWindowPos(this->m_hMainHwnd, HWND_TOP,
                 0, 0, 0, 0, SWP_NOSIZE | SWP_NOCOPYBITS);
    rapidjson::Document& aiTreeConf = CONFIG_INSTANCE->GetImageMatchTree();
    behavior::BehaviorNode* aiTree = BTCFactory::GenerateAITree(aiTreeConf);
    this->SetAiTree(aiTree);
    return true;
}

HWND &ImageMatchAI::GetClientHwnd() {
    if (this->m_hClientHwnd == nullptr){
        return this->m_hMainHwnd;
    }
    return this->m_hClientHwnd;
}

HWND &ImageMatchAI::GetMainHwnd() {
    return this->m_hMainHwnd;
}

void ImageMatchAI::ExecuteMouseClick(POINT point) {
    ClientToScreen(this->m_hClientHwnd, &point);
//    SetCursorPos(point.x, point.y);
//    ::SetForegroundWindow(this->m_hClientHwnd);
    printf("ClientToScreen x:%d, y:%d\n", point.x, point.y);
    PostMessage(this->m_hClientHwnd, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(point.x, point.y));
    PostMessage(this->m_hClientHwnd, WM_LBUTTONUP, 0, MAKELPARAM(point.x, point.y));
}

void ImageMatchAI::SetAiTree(behavior::BehaviorNode *aiTree) {
    BTCFactory::PrintfRootNode(aiTree);
    this->m_aiTree = aiTree;
}

cv::Mat ImageMatchAI::CreateMat() {
    int width = 0;
    int height = 0;
    GetWindowWidthHeight(this->m_hClientHwnd, width, height);
    return cv::Mat(height, width, CV_8UC4);
}

int ImageMatchAI::ExecuteAiTree() {
    JUDGE_RETURN(this->m_aiTree != nullptr, -1);
    BevNodeInputParam input;
    input.ai = this;
    JUDGE_RETURN(this->m_aiTree->Evaluate(input) == true, -1);
    BevNodeInputParam output;
    output.ai = this;
    this->m_aiTree->Tick(input, output);
    return 0;
}
