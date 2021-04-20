//
// Created by iWong on 29/3/2021.
//

#include "tools.h"
#include "psapi.h"
#include "winver.h"

struct NTCREATETHREAD_BUFFER  {
    ULONG     m_size;
    ULONG     m_unknown1;
    ULONG     m_unknown2;
    PULONG    m_unknown3;
    ULONG     m_unknown4;
    ULONG     m_unknown5;
    ULONG     m_unknown6;
    PULONG    m_unknown7;
    ULONG     m_unknown8;
};

typedef NTSTATUS ( __stdcall *NTCREATETHREADEX) (
        PHANDLE thread,
        ACCESS_MASK desired_access,
        LPVOID object_attributes,
        HANDLE process_handle,
        LPTHREAD_START_ROUTINE start_address,
        LPVOID lp,
        BOOL create_suspended,
        ULONG stack_zero_bits,
        ULONG size_of_stack_commit,
        ULONG size_of_stack_reserve,
        LPVOID bytes_buffer );


typedef NTSTATUS(WINAPI* LPFN_NTCREATETHREADEX)(
        OUT PHANDLE ThreadHandle,
        IN ACCESS_MASK DesiredAccess,
        IN LPVOID ObjectAttributes,
        IN HANDLE ProcessHandle,
        IN LPTHREAD_START_ROUTINE ThreadProcedure,
        IN LPVOID ParameterData,
        IN BOOL CreateSuspended,
        IN SIZE_T StackZeroBits,
        IN SIZE_T SizeOfStackCommit,
        IN SIZE_T SizeOfStackReserve,
        OUT LPVOID BytesBuffer);

HWND GetWindowHwnd(const std::string& className){
    HWND hwnd = FindWindow(className.c_str(), nullptr);
    if(nullptr == hwnd){
        MessageBox(nullptr, "process not run", "error", MB_OKCANCEL | MB_ICONHAND);
        return nullptr;
    }
    return hwnd;
}

void GetProcessPathByPid(DWORD& pid, char* path){
    HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (nullptr == handle) {
        MessageBox(nullptr, "process not run", "error", MB_OKCANCEL | MB_ICONHAND);
        return;
    }
    GetModuleFileNameEx(handle, nullptr, path, MAX_PATH);
}

void GetProcessPathByHwnd(const HWND& hwnd, char* path){
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    GetProcessPathByPid(pid, path);
}

void GetProcessVersion(char* path, char* version){
    DWORD handle;
    DWORD versionInfoSize = GetFileVersionInfoSize(path, &handle);
    BYTE *versionInfo = new BYTE[versionInfoSize];
    if (FALSE == GetFileVersionInfo(path, 0, versionInfoSize, versionInfo)) {
        delete[] versionInfo;
        return;
    }
    VS_FIXEDFILEINFO* p_version = nullptr;
    unsigned int len;
    if(FALSE == VerQueryValue(versionInfo, TEXT("\\"), (void**)&p_version, &len)){
        return;
    }
    version[0] = HIWORD(p_version->dwFileVersionMS);
    version[1] = LOWORD(p_version->dwFileVersionMS);
    version[2] = HIWORD(p_version->dwFileVersionLS);
    version[3] = LOWORD(p_version->dwFileVersionLS);
    delete[] versionInfo;
}

DWORD GetProcessIDByName(const std::string& name){
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return 0;
    }
    PROCESSENTRY32 pe = {sizeof(pe)};
    for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe)) {
        if(strcmp(name.c_str(), pe.szExeFile) == 0){
            std::cout << "process name:" << pe.szExeFile << std::endl;
//            HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, pe.th32ProcessID);
            CloseHandle(hSnapshot);
            return pe.th32ProcessID;
        }
    }
    CloseHandle(hSnapshot);
    return 0;
}


void GetProcessTitleAndVersion(const HWND& hwnd, std::string &titleVersion) {
    char version[VERSION_MAX] = {0};
    char path[MAX_PATH] = {0};
    char title[MAX_PATH] = {0};
    GetProcessPathByHwnd(hwnd, path);
    GetProcessVersion(path, version);
    GetWindowText(hwnd, title, MAX_PATH);
    titleVersion = title;
    titleVersion.append(" ");
    for(auto versionByte : version) {
        titleVersion.append(std::to_string(versionByte)).append(".");
    }
    titleVersion.pop_back();
}


void GetProcessHwndVecByClassName(const std::string& className, EnumHwndArg& eHwndArgs){
    eHwndArgs.dwClassName = className;
    eHwndArgs.dwHwndVec = new std::vector<HWND>;

    EnumWindows(lpEnumFunc, (LPARAM)&eHwndArgs);
}


BOOL CALLBACK lpEnumFunc(HWND hwnd, LPARAM lParam){
    auto *pArgs = (LPEnumHwndArg)lParam;
    char className[MAX_PATH];
    GetClassName(hwnd,className, MAX_PATH);
    if(strcmp(className, pArgs->dwClassName.c_str()) == 0){
        pArgs->dwHwndVec->push_back(hwnd);
    }
    return TRUE;
}

void WindowCapture(const HWND &hwnd, cv::Mat &searchImg) {
    JUDGE_RETURN(hwnd != nullptr, ;);
    int width = 0;
    int height = 0;
    GetWindowWidthHeight(hwnd, width, height);
    int bmpSize = width * height * 4;
    searchImg.create(height, width, CV_8UC4);

    HDC hSrcDC = GetDC(hwnd);
    HDC hMemDC = CreateCompatibleDC(hSrcDC);
    HBITMAP hMemBMP = CreateCompatibleBitmap(hSrcDC, width, height);
    static_cast<HBITMAP>(SelectObject(hMemDC, hMemBMP));
    BitBlt(hMemDC, 0, 0, width, height, hSrcDC, 0, 0, SRCCOPY | CAPTUREBLT);
    GetBitmapBits(hMemBMP, bmpSize, searchImg.data);
    DeleteObject(hMemBMP);
    DeleteDC(hMemDC);
    ReleaseDC(hwnd, hSrcDC);
}

double GetWindowDpiScaleFactor() {
    auto fGetDpiForWindow = (GetDpiForWindow) GetProcAddress(GetModuleHandle(TEXT("User32")), "GetDpiForWindow");
    JUDGE_RETURN(fGetDpiForWindow != nullptr, 1);
    HWND desktopHwnd = GetDesktopWindow();
    int dpi = (*fGetDpiForWindow)(desktopHwnd);
    switch (dpi) {
        case DPI_SCALE_FACTOR_100:
            return 1;
        case DPI_SCALE_FACTOR_125:
            return 1.25;
        case DPI_SCALE_FACTOR_150:
            return 1.5;
        case DPI_SCALE_FACTOR_200:
            return 2;
        default:
            return 1;
    }
}

void GetWindowWidthHeight(HWND hwnd, int& width, int& height){
    double dpiScaleFactor = GetWindowDpiScaleFactor();
    RECT rc;
    GetWindowRect(hwnd, &rc);
    width = int((rc.right - rc.left) * dpiScaleFactor);
    height = int((rc.bottom - rc.top) * dpiScaleFactor);
}

bool IsIrregularRectangle(const std::vector<cv::Point2f>& posList){
    for (int i = 0; i < posList.size(); i++) {
        for (int j = 0; j < posList.size(); j++) {
            if (i == j) continue;
            if (posList[i].x == posList[j].x && posList[i].y == posList[j].y)
                return false;
        }
    }
    JUDGE_RETURN(posList[0].x < posList[1].x, false);
    JUDGE_RETURN(posList[0].x < posList[2].x, false);
    JUDGE_RETURN(posList[1].y < posList[2].y, false);
    JUDGE_RETURN(posList[1].y < posList[3].y, false);
    JUDGE_RETURN(posList[2].x > posList[0].x, false);
    JUDGE_RETURN(posList[2].x > posList[3].x, false);

    return true;
}

bool IsInIrregularRectangle(const std::vector<cv::Point2f> &rectPos, cv::Point2f &pos) {
    bool IsInXRange = pos.x >= rectPos[0].x && pos.x >= rectPos[3].x && pos.x <= rectPos[1].x and pos.x <= rectPos[2].x;
    bool IsInYRange = pos.y >= rectPos[0].y && pos.y >= rectPos[1].y && pos.y <= rectPos[2].y and pos.y <= rectPos[3].y;
    return IsInXRange && IsInYRange;
}