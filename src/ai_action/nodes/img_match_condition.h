//
// Created by iWong on 27/3/2021.
//

#ifndef BEHAVIORTREE_IMG_MATCH_CONDITION_H
#define BEHAVIORTREE_IMG_MATCH_CONDITION_H
#include "conditions/conditions.h"
#include "opencv2/highgui.hpp"
#include "image_matcher/ImageMatcher.h"

namespace image_match {
    class AIIMConditionBase : public behavior::ConditionBase {
    public:
        AIIMConditionBase() = default;

        ~AIIMConditionBase() override = default;

        virtual bool ExternalCondition(const BevNodeInputParam& input);
        void LoadTmplImage(std::__cxx11::string& path);

    protected:
        int &GetMatchType();

        int &GetModeType();

        int m_matchType{cv::TM_SQDIFF_NORMED};
        int m_modeType{ImageMatcher::E_TEMPLATE_MATCHER};
        cv::Mat GetTmplImage();
        cv::Mat m_tmplImage;

    private:
        virtual bool AIIMExternalCondition(const BevNodeInputParam &input);

    };

    class AIIMAppRunning : public AIIMConditionBase{
    public:
        AIIMAppRunning() = default;
        ~AIIMAppRunning() override = default;

    private:
        virtual bool AIIMInternalCondition(const BevNodeInputParam &input);

    };

    class AIIMOnObjScreenUI : public AIIMConditionBase{
    public:
        AIIMOnObjScreenUI() = default;
        ~AIIMOnObjScreenUI() override = default;

    private:
        virtual bool AIIMInternalCondition(const BevNodeInputParam &input);

    };

}

#endif //BEHAVIORTREE_IMG_MATCH_CONDITION_H
