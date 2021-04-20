cmake_minimum_required(VERSION 3.17)
project(_ImageMatch)

set(CMAKE_CXX_STANDARD 14)

#set(OpenCV_DIR "H:/opencv/build/x64/VSRelease/install/x64/vc16/lib")
#set(OpenCV_DIR "H:/opencv/build/x64/VSDebug")

set(OpenCV_DIR "H:/opencv/build/x64/MinGWDebugExtra/install")
#set(CMAKE_BUILD_TYPE Debug)
find_package(OpenCV REQUIRED)
include_directories(src/behavior ${OpenCV_INCLUDE_DIRS} src)

link_directories(${OpenCV_LIBRARY_DIRS})

MESSAGE(STATUS "${OpenCV_INCLUDE_DIRS}\n")
MESSAGE(STATUS "library dir ${OpenCV_LIBRARY_DIRS}\n")
MESSAGE(STATUS "${OpenCV_LIBS}\n")

add_executable(_ImageMatch
        src/main.cpp
        src/behavior/behavior_tree.h
        src/behavior/behavior_tree.cpp
        src/behavior/conditions/conditions.h
        src/behavior/conditions/conditions.cpp
        src/behavior/conditions/condition_operator.h
        src/behavior/conditions/condition_operator.cpp
        src/behavior/nodes/control/selector.h
        src/behavior/nodes/control/selector.cpp
        src/behavior/nodes/control/sequence.h
        src/behavior/nodes/control/sequence.cpp
        src/behavior/nodes/control/parallel.h
        src/behavior/nodes/control/parallel.cpp
        src/behavior/nodes/action/action.h
        src/behavior/nodes/action/action.cpp
        src/ai_action/nodes/img_match_action.h
        src/ai_action/nodes/img_match_action.cpp
        src/ai_action/nodes/img_match_condition.h
        src/ai_action/nodes/img_match_condition.cpp
        src/ai_action/img_match_ai.h
        src/ai_action/img_match_ai.cpp
        src/tool/tools.h
        src/tool/tools.cpp
        src/image_matcher/ImageMatcher.h
        src/image_matcher/ImageMatcher.cpp)
target_link_libraries(_ImageMatch ${OpenCV_LIBS} psapi Version dxgi)