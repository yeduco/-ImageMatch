//
// Created by iWong on 21/4/2021.
//

#include "public/configure.h"

void Configure::init() {
    LoadJsonConfig(this->m_base, (char*)("..\\src\\config.json"));
    LoadJsonConfig(this->m_bevTree, (char*)("..\\src\\config.json"));
}

void Configure::LoadJsonConfig(Document &doc, char* path) {
    printf("%s", path);
    FILE* pFile = fopen(path, "rb");
    JUDGE_RETURN(pFile != nullptr, ;);
    char readBuffer[65535];
    FileReadStream inputStream(pFile, readBuffer, sizeof(readBuffer));
    doc.ParseStream(inputStream);
    fclose(pFile);
}
