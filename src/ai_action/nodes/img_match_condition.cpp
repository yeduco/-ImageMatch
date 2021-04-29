//
// Created by iWong on 27/3/2021.
//

#include "img_match_condition.h"
#include "ai_action/img_match_ai.h"
//#include "image_matcher/ImageMatcher.h"
#include "include.h"

namespace image_match{

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
        printf("%s\n", path.c_str());
        this->m_tmplImage = cv::imread(path, cv::IMREAD_ANYCOLOR);
    }

    bool AIIMConditionBase::ExternalCondition(const BevNodeInputParam &input) {
        JUDGE_RETURN(input.ai != nullptr, false);
        return this->AIIMExternalCondition(input);
    }

    void AIIMConditionBase::SetMatchType(int type) {
        this->m_matchType = type;
    }

    void AIIMConditionBase::SetModeType(int type) {
        this->m_modeType = type;
    }

    bool AIIMAppRunning::AIIMExternalCondition(const BevNodeInputParam &input) {
        ImageMatchAI* ai = input.ai;
        return ::IsWindow(ai->GetMainHwnd());
    }

    bool AIIMOnObjScreenUI::AIIMExternalCondition(const BevNodeInputParam &input) {
        ImageMatchAI* ai = input.ai;
        HWND& hwnd = ai->GetClientHwnd();
        cv::Mat mainImage;
        ai->CreateMat().copyTo(mainImage);
        JUDGE_RETURN(ImageMatcherApi::CaptureScreen(hwnd, mainImage), false);
        cv::Mat tmplImage;
        this->GetTmplImage().copyTo(tmplImage);

        std::tuple<bool, int, int, cv::Mat> result = ImageMatcherApi::Match(tmplImage, mainImage, this->GetModeType(), this->GetMatchType());
        bool isMatch = std::get<0>(result);
        return isMatch;
    }

}