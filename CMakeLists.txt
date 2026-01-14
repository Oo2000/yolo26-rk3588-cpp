# 设置最低版本号
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
# 设置项目名称
project(rk3588-demo VERSION 0.0.1 LANGUAGES CXX)

# 输出系统信息
message(STATUS "System: ${CMAKE_SYSTEM_NAME} ${CMAKE_SYSTEM_VERSION}")

# 设置编译器
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置库架构
set(LIB_ARCH "aarch64")
set(DEVICE_NAME "RK3588")

link_directories(
    mpp_libs
)

#  rknn_api 文件夹路径
set(RKNN_API_PATH ${CMAKE_CURRENT_SOURCE_DIR}/librknn_api)
#  rknn_api include 路径
set(RKNN_API_INCLUDE_PATH ${RKNN_API_PATH}/include)
#  rknn_api lib 路径
set(RKNN_API_LIB_PATH ${RKNN_API_PATH}/${LIB_ARCH}/librknnrt.so)

# 寻找OpenCV库，使用自定义的OpenCV_DIR
find_package(OpenCV REQUIRED)
# 输出OpenCV信息
message(STATUS "include path: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "${OpenCV_VERSION}")

# 寻找Eigen3
set(EIGEN_VERSION 3.3)
find_package(Eigen3 ${EIGEN_VERSION} QUIET)

# 用来搜索头文件的目录
include_directories(
    ${OpenCV_INCLUDE_DIRS}
    ${RKNN_API_INCLUDE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/src

)


# 构建预处理和后处理库
add_library(nn_process SHARED
            src/process/preprocess.cpp
            src/process/postprocess.cpp
)
# 链接库
target_link_libraries(nn_process
    ${OpenCV_LIBS}
)

# 构建自定义封装API库
add_library(rknn_engine SHARED src/engine/rknn_engine.cpp) 
# 链接库
target_link_libraries(rknn_engine
    ${RKNN_API_LIB_PATH}
)
# yolo26_lib
add_library(yolo26_lib SHARED src/task/yolo26.cpp)
# 链接库
target_link_libraries(yolo26_lib
    rknn_engine
    nn_process
)

# draw_lib
add_library(draw_lib SHARED src/draw/cv_draw.cpp)
# 链接库
target_link_libraries(draw_lib
    ${OpenCV_LIBS}
)

# yolo26_img
add_executable(yolo26_img src/yolo26_img.cpp)

# 链接库
target_link_libraries(yolo26_img
        draw_lib
        yolo26_lib
)

add_executable(yolo26_video src/yolo26_video.cpp)

# 链接库
target_link_libraries(yolo26_video
        draw_lib
        yolo26_lib
)

# yolo26_imgs
add_executable(yolo26_imgs src/yolo26_imgs.cpp)

# 链接库
target_link_libraries(yolo26_imgs
        draw_lib
        yolo26_lib
)

