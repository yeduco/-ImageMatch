cmake_minimum_required(VERSION 3.17)
project(_ImageMatch)

set(CMAKE_CXX_STANDARD 11)

#set(OpenCV_DIR "H:/opencv/build/x64/VSRelease/install/x64/vc16/lib")
#set(OpenCV_DIR "H:/opencv/build/x64/VSDebug")

set(OpenCV_DIR "H:/opencv/build/x64/MinGWDebugExtra/install")
#set(CMAKE_BUILD_TYPE Debug)
find_package(OpenCV REQUIRED)
include_directories(src/behavior
        ${OpenCV_INCLUDE_DIRS}
        src
        src/include
        src/include/rapidjson
        src/include/rapidjson/error
        src/include/rapidjson/internal)

link_directories(${OpenCV_LIBRARY_DIRS})

MESSAGE(STATUS "${OpenCV_INCLUDE_DIRS}\n")
MESSAGE(STATUS "library dir ${OpenCV_LIBRARY_DIRS}\n")
MESSAGE(STATUS "${OpenCV_LIBS}\n")

#file(GLOB SOURCE_LIST "src/ai_action/*.h" "src/ai_action/*.cpp")
#
#MESSAGE(STATUS "${SOURCE_LIST}\n")

aux_source_directory(src SRCS)
aux_source_directory(src/ai_action AI_ACTION)
aux_source_directory(src/ai_action/nodes AI_ACTION_NODES)
aux_source_directory(src/behavior BEV)
aux_source_directory(src/behavior/conditions BEV_CONDITIONS)
aux_source_directory(src/behavior/nodes/action BEV_NODES_ACTION)
aux_source_directory(src/behavior/nodes/control BEV_NODES_CONTROL)
aux_source_directory(src/image_matcher IMAGE_MATCHER)
aux_source_directory(src/public PUBLIC)

MESSAGE(STATUS "${SRCS}\n")

SET(SOURCE_LIST
        ${SRCS}
        ${AI_ACTION}
        ${AI_ACTION_NODES}
        ${BEV}
        ${BEV_CONDITIONS}
        ${BEV_NODES_ACTION}
        ${BEV_NODES_CONTROL}
        ${IMAGE_MATCHER}
        ${PUBLIC})

MESSAGE(STATUS "${SOURCE_LIST}\n")

add_executable(_ImageMatch ${SOURCE_LIST})
target_link_libraries(_ImageMatch ${OpenCV_LIBS} psapi Version dxgi)