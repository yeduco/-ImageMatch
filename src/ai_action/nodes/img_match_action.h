//
// Created by iWong on 26/3/2021.
//

#ifndef BEHAVIORTREE_IMG_MATCH_ACTION_H
#define BEHAVIORTREE_IMG_MATCH_ACTION_H

#include "behavior_tree.h"
#include "nodes/action/action.h"
#include "opencv2/highgui.hpp"

namespace image_match {
    class AIIMBaseAction : public behavior::BevActionNode {
    public:
        AIIMBaseAction() = default;

        ~AIIMBaseAction() override = default;

    protected:
        int DoExecute(const behavior::BevNodeInputParam &input) override;

        virtual int AIIMExecute(const behavior::BevNodeInputParam &input);

        cv::Mat GetTmplImage();

        cv::Mat m_tmplImage;
    };

    class AIIMClickAction : public AIIMBaseAction {
    protected:
        int AIIMExecute(const behavior::BevNodeInputParam &input) override;
    };
}
#endif //BEHAVIORTREE_IMG_MATCH_ACTION_H
