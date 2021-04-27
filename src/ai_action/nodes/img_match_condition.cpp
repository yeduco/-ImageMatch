//
// Created by iWong on 27/3/2021.
//

#include "img_match_condition.h"
#include "ai_action/img_match_ai.h"
//#include "image_matcher/ImageMatcher.h"
#include "include.h"

namespace image_match{


    bool AIIMConditionBase::AIIMExternalCondition(const BevNodeInputParam &input) {
        return true;
    }

    cv::Mat AIIMConditionBase::GetTmplImage() {
        return this->m_tmplImage;
    }

    int &AIIMConditionBase::GetMatchType() {
        return this->m_matchType;
    }

    int &AIIMConditionBase::GetModeType() {
        return this->m_modeType;
    }

    void AIIMConditionBase::LoadTmplImage(std::string &path) {
        this->m_tmplImage = cv::imread(path, cv::IMREAD_ANYCOLOR);
    }

    bool AIIMConditionBase::ExternalCondition(const BevNodeInputParam &input) {
        JUDGE_RETURN(input.ai != nullptr, false);
        return this->AIIMExternalCondition(input);
    }

    bool AIIMAppRunning::AIIMInternalCondition(const BevNodeInputParam &input) {
        ImageMatchAI* ai = input.ai;
        return ::IsWindow(ai->GetMainHwnd());
    }

    bool AIIMOnObjScreenUI::AIIMInternalCondition(const BevNodeInputParam &input) {
        ImageMatchAI* ai = input.ai;
        HWND& hwnd = ai->GetClientHwnd();
        cv::Mat mainImage = ai->CreateMat();
        JUDGE_RETURN(ImageMatcher::CaptureScreen(hwnd, mainImage), false);
        cv::Mat tmplImage = this->GetTmplImage();
        std::tuple<bool, int, int, cv::Mat> result = ImageMatcher::Match(tmplImage, mainImage, this->GetMatchType(), this->GetMatchType());
        bool isMatch = std::get<0>(result);
        return isMatch;
    }

}