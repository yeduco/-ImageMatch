//
// Created by iWong on 21/4/2021.
//

#include "public/configure.h"
#include "btc_factory/BTCFactory.h"

void Configure::init() {
    LoadJsonConfig(this->m_baseConfig, (char*)(R"(..\src\config\base_config.json)"));
    LoadJsonConfig(this->m_imageMatchTree, (char*)(R"(..\src\config\image_match.json)"));
}

void Configure::LoadJsonConfig(Document &doc, char* path) {
    FILE* pFile = fopen(path, "rb");
    JUDGE_RETURN(pFile != nullptr, ;);
    char readBuffer[65535];
    FileReadStream inputStream(pFile, readBuffer, sizeof(readBuffer));
    doc.ParseStream(inputStream);
    fclose(pFile);
    auto aiTree = BTCFactory::GenerateAITree(this->m_imageMatchTree);
    BTCFactory::PrintfRootNode(aiTree);
}

Document &Configure::GetBaseConfig() {
    return this->m_baseConfig;
}

Document &Configure::GetImageMatchTree() {
    return this->m_imageMatchTree;
}
