//
// Created by iWong on 21/4/2021.
//

#ifndef _IMAGEMATCH_CONFIGURE_H
#define _IMAGEMATCH_CONFIGURE_H

#include "include/singleton.h"
#include "include.h"
using namespace rapidjson;

class Configure {
public:
    Configure() = default;

    ~Configure() = default;

    void init();

    static void LoadJsonConfig(Document &doc, const std::string& path);

    Document& GetBaseConfig();
    Document& GetImageMatchTree();

private:
    Document m_baseConfig;
    Document m_imageMatchTree;
};


typedef Singleton<Configure> ConfigSingle;
#define CONFIG_INSTANCE (ConfigSingle::Instance())

#endif //_IMAGEMATCH_CONFIGURE_H
