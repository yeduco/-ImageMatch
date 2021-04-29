//
// Created by iWong on 26/3/2021.
//

#include "img_match_action.h"

int image_match::AIIMBaseAction::DoExecute(const BevNodeInputParam &input) {
    JUDGE_RETURN(input.ai != nullptr, BT_SUCCESS);
    int ret = this->AIIMExecute(input);
    return ret;
}

cv::Mat image_match::AIIMBaseAction::GetTmplImage() {
    return this->m_tmplImage;
}

int &image_match::AIIMBaseAction::GetMatchType() {
    return this->m_matchType;
}

int &image_match::AIIMBaseAction::GetModeType() {
    return this->m_modeType;
}

void image_match::AIIMBaseAction::LoadTmplImage(std::__cxx11::string &path) {
    this->m_tmplImage = cv::imread(path, cv::IMREAD_ANYCOLOR);
}

void image_match::AIIMBaseAction::SetMatchType(int type) {
    this->m_matchType = type;
}

void image_match::AIIMBaseAction::SetModeType(int type) {
    this->m_modeType = type;
}

void image_match::AIIMBaseAction::SetCoordinate(int x, int y) {
    this->m_useCoordinate = true;
    this->m_coordinate.x = x;
    this->m_coordinate.y = y;
}

POINT &image_match::AIIMBaseAction::GetCoordinate() {
    return this->m_coordinate;
}

bool image_match::AIIMBaseAction::UseCoordinate() {
    return this->m_useCoordinate;
}

int image_match::AIIMClickAction::AIIMExecute(const BevNodeInputParam &input) {
    std::cout << "nodeName:" << this->GetFieldName() << " click action" << std::endl;
    ImageMatchAI* ai = input.ai;
    HWND& hwnd = ai->GetClientHwnd();
    cv::Mat mainImage;
    ai->CreateMat().copyTo(mainImage);
    cv::Mat tmplImage;
    this->GetTmplImage().copyTo(tmplImage);
    JUDGE_RETURN(ImageMatcherApi::CaptureScreen(hwnd, mainImage), BT_FAILURE);
    std::tuple<bool, int, int, cv::Mat> result = ImageMatcherApi::Match(tmplImage, mainImage, this->GetModeType(), this->GetMatchType());
    if (std::get<0>(result)) {
        POINT point;
        point.x = std::get<1>(result);
        point.y = std::get<2>(result);
        ai->ExecuteMouseClick(point);
        return BT_SUCCESS;
    } else {
        return BT_FAILURE;
    }
}
