//
// Created by iWong on 26/3/2021.
//

#ifndef BEHAVIORTREE_TEST_H
#define BEHAVIORTREE_TEST_H

#include <utility>

#include "string"

class TSIMData{
public:
    TSIMData() = default;

    ~TSIMData() = default;

    void SetName(std::string name) { this->m_name = std::move(name); };

    std::string &GetName() { return this->m_name; };
private:
    std::string m_name{};

};


#endif //BEHAVIORTREE_TEST_H
