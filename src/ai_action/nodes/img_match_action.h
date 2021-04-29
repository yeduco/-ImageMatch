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

        void SetMatchType(int type);
        void SetModeType(int type);
        void SetCoordinate(int x, int y);

    protected:
        int DoExecute(const BevNodeInputParam &input) override;

        virtual int AIIMExecute(const BevNodeInputParam &input) = 0;

        cv::Mat GetTmplImage();

        POINT &GetCoordinate();

        int &GetMatchType();

        int &GetModeType();

        bool UseCoordinate();

        int m_matchType{cv::TM_CCOEFF_NORMED};
        int m_modeType{ImageMatcherApi::E_TEMPLATE_MATCHER};
        cv::Mat m_tmplImage;
        POINT m_coordinate{};
        bool m_useCoordinate{false};
    };

    class AIIMClickAction : public AIIMBaseAction {
    protected:
        int AIIMExecute(const BevNodeInputParam &input) override;
    };
}
#endif //BEHAVIORTREE_IMG_MATCH_ACTION_H
