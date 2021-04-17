//
// Created by iWong on 27/3/2021.
//

#include "img_match_condition.h"

namespace image_match{

    bool AIIMConditionBase::ExternalCondition(const behavior::BevNodeInputParam &input) {

        return this->AIIMExternalCondition(input);
    }

    bool AIIMConditionBase::AIIMExternalCondition(const behavior::BevNodeInputParam &input) {
        return true;
    }

    bool AIIMCondMatchSuccess::AIIMInternalCondition(const behavior::BevNodeInputParam &input) {
        return true;
    }
}