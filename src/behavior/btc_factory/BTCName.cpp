//
// Created by iWong on 25/4/2021.
//

#include "BTCName.h"
/*===================== node type =========================*/
std::__cxx11::string BTCName::ActionNode = "action";
std::__cxx11::string BTCName::ControlNode = "control";
std::__cxx11::string BTCName::ConditionNode = "condition";

/*===================== action node name =========================*/
std::__cxx11::string BTCName::ActionClickUI = "ClickUI";

/*===================== control node name =========================*/
std::__cxx11::string BTCName::ControlSelector = "Selector";
std::__cxx11::string BTCName::ControlSequence = "Sequence";
std::__cxx11::string BTCName::ControlParallel = "Parallel";

/*===================== Condition node name =========================*/
std::__cxx11::string BTCName::ConditionAppRunning = "AppRunning";
std::__cxx11::string BTCName::ConditionOnObjScreen = "OnObjScreen";