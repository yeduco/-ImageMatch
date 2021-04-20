//
// Created by iWong on 29/3/2021.
//

#ifndef BEHAVIORTREE_TOOLS_H
#define BEHAVIORTREE_TOOLS_H

#include "Windows.h"
#include "iostream"
#include "string"
#include "tlhelp32.h"
#include "vector"
#include "opencv2/opencv.hpp"

typedef struct EnumHwndArg{
    std::vector<HWND> *dwHwndVec{};
    std::string dwClassName;
}EnumHwndArg, *LPEnumHwndArg;

#define VERSION_MAX 4
#define JUDGE_RETURN(CONDITION, RETURN) if (!(CONDITION)){return RETURN;}
typedef int (WINAPI *GetDpiForWindow)(HWND hwnd);

#define DPI_SCALE_FACTOR_100 96
#define DPI_SCALE_FACTOR_125 120
#define DPI_SCALE_FACTOR_150 144
#define DPI_SCALE_FACTOR_200 192

HWND GetWindowHwnd(const std::string& className);

void GetProcessPathByPid(DWORD& pid, char* path);

void GetProcessPathByHwnd(const HWND& hwnd, char* path);

void GetProcessVersion(char* path, char* version);

DWORD GetProcessIDByName(const std::string& name);

void GetProcessTitleAndVersion(const HWND &hwnd, std::string& titleVersion);

void GetProcessHwndVecByClassName(const std::string& className, EnumHwndArg& eHwndArgs);

BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam);

void WindowCapture(const HWND& hwnd, cv::Mat& searchImg);

double GetWindowDpiScaleFactor();

void GetWindowWidthHeight(HWND hwnd, int& width, int& height);

//判断是否是一个不规则矩阵
bool IsIrregularRectangle(const std::vector<cv::Point2f>& pos);

//判断坐标是否在矩阵内
bool IsInIrregularRectangle(const std::vector<cv::Point2f>& rectPos, cv::Point2f& pos);


#endif //BEHAVIORTREE_TOOLS_H
