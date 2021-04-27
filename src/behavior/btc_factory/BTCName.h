//
// Created by iWong on 25/4/2021.
//

#ifndef _IMAGEMATCH_BTCFIEXDNAME_H
#define _IMAGEMATCH_BTCFIEXDNAME_H
#include <string>

struct BTCName {
    /*===================== node type =========================*/
    static std::__cxx11::string ActionNode;
    static std::__cxx11::string ControlNode;
    static std::__cxx11::string ConditionNode;

    /*===================== action node name =========================*/
    static std::__cxx11::string ActionClickUI;

    /*===================== control node name =========================*/
    static std::__cxx11::string ControlSelector;
    static std::__cxx11::string ControlSequence;
    static std::__cxx11::string ControlParallel;

    /*===================== Condition node name =========================*/
    static std::__cxx11::string ConditionAppRunning;
    static std::__cxx11::string ConditionOnObjScreen;
};


#endif //_IMAGEMATCH_BTCFIEXDNAME_H
