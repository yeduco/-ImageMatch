//
// Created by iWong on 26/3/2021.
//

#ifndef BEHAVIORTREE_IMG_MATCH_ACTION_H
#define BEHAVIORTREE_IMG_MATCH_ACTION_H

#include "behavior_tree.h"
#include "nodes/action/action.h"
#include "opencv2/highgui.hpp"
#include "ai_action/img_match_ai.h"

namespace image_match {
    class AIIMBaseAction : public behavior::BevActionNode {
    public:
        AIIMBaseAction() = default;

        ~AIIMBaseAction() override = default;
        void LoadTmplImage(std::__cxx11::string& path);

    protected:
        int DoExecute(const BevNodeInputParam &input) override;

        virtual int AIIMExecute(const BevNodeInputParam &input);

        cv::Mat GetTmplImage();


        int &GetMatchType();

        int &GetModeType();

        int m_matchType{cv::TM_SQDIFF_NORMED};
        int m_modeType{ImageMatcher::E_TEMPLATE_MATCHER};
        cv::Mat m_tmplImage;
    };

    class AIIMClickAction : public AIIMBaseAction {
    protected:
        int AIIMExecute(const BevNodeInputParam &input) override;
    };
}
#endif //BEHAVIORTREE_IMG_MATCH_ACTION_H
