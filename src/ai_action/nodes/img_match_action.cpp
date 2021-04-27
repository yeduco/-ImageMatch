//
// Created by iWong on 26/3/2021.
//

#include "img_match_action.h"

int image_match::AIIMBaseAction::DoExecute(const BevNodeInputParam &input) {
    JUDGE_RETURN(input.ai != nullptr, BT_SUCCESS);
    int ret = this->AIIMExecute(input);
    return ret;
}

int image_match::AIIMBaseAction::AIIMExecute(const BevNodeInputParam &input) {
    return BT_SUCCESS;
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

int image_match::AIIMClickAction::AIIMExecute(const BevNodeInputParam &input) {
    std::cout << "nodeName:" << this->GetFieldName() << " click action" << std::endl;
    ImageMatchAI* ai = input.ai;
    HWND& hwnd = ai->GetClientHwnd();
    cv::Mat mainImage = ai->CreateMat();
    cv::Mat tmplImage = this->GetTmplImage();
    std::tuple<bool, int, int, cv::Mat> result = ImageMatcher::Match(tmplImage, mainImage, this->GetModeType(), this->GetMatchType());
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
