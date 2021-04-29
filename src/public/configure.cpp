//
// Created by iWong on 21/4/2021.
//

#include "public/configure.h"
#include "btc_factory/BTCFactory.h"

void Configure::init() {
//    LoadJsonConfig(this->m_baseConfig, (char*)("..\\src\\config\\base_config.json"));
//    LoadJsonConfig(this->m_imageMatchTree, (char*)("..\\src\\config\\image_match.json"));
//    std::string baseConfigPath = R"(..\src\config\base_config.json)";

    LoadJsonConfig(this->m_baseConfig, R"(..\src\config\base_config.json)");
    LoadJsonConfig(this->m_imageMatchTree, R"(..\src\config\image_match.json)");
}

void Configure::LoadJsonConfig(Document &doc, const std::string& path) {
    FILE* pFile = fopen(path.c_str(), "rb");
    JUDGE_RETURN(pFile != nullptr, ;);
    char readBuffer[65535];
    FileReadStream inputStream(pFile, readBuffer, sizeof(readBuffer));
    doc.ParseStream(inputStream);
    fclose(pFile);
}

Document &Configure::GetBaseConfig() {
    return this->m_baseConfig;
}

Document &Configure::GetImageMatchTree() {
    return this->m_imageMatchTree;
}
