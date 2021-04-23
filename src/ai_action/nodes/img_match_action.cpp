//
// Created by iWong on 26/3/2021.
//

#include "img_match_action.h"

int image_match::AIIMBaseAction::DoExecute(const behavior::BevNodeInputParam &input) {
    JUDGE_RETURN(input.m_data != nullptr, BT_SUCCESS);
    int ret = this->AIIMExecute(input);
    return ret;
}

int image_match::AIIMBaseAction::AIIMExecute(const behavior::BevNodeInputParam &input) {
    return BT_SUCCESS;
}

cv::Mat image_match::AIIMBaseAction::GetTmplImage() {
    return this->m_tmplImage;
}

int image_match::AIIMClickAction::AIIMExecute(const behavior::BevNodeInputParam &input) {
    std::cout << "nodeName:" << this->GetFileName() << " click action" << std::endl;
    return BT_SUCCESS;
}
