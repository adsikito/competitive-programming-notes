cmake_minimum_required(VERSION 2.8)

project(tftp_server)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加可执行程序
add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/tftp_server.cpp)

# 添加相关的路径
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/header)