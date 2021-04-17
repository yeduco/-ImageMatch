//
// Created by iWong on 27/3/2021.
//

#ifndef BEHAVIORTREE_IMG_MATCH_CONDITION_H
#define BEHAVIORTREE_IMG_MATCH_CONDITION_H
#include "conditions/conditions.h"

namespace image_match {
    class AIIMConditionBase : public behavior::ConditionBase {
    public:
        AIIMConditionBase() = default;

        ~AIIMConditionBase() override = default;

        virtual bool ExternalCondition(const behavior::BevNodeInputParam& input);

    private:
        virtual bool AIIMExternalCondition(const behavior::BevNodeInputParam &input);

    };

    class AIIMCondMatchSuccess : public AIIMConditionBase{
    public:
        AIIMCondMatchSuccess() = default;
        ~AIIMCondMatchSuccess() override = default;

    private:
        virtual bool AIIMInternalCondition(const behavior::BevNodeInputParam &input);

    };

}

#endif //BEHAVIORTREE_IMG_MATCH_CONDITION_H
