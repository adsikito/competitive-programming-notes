# 规定最小版本
cmake_minimum_required(VERSION 2.8)

# 项目名称
project(thttpd)

# 添加可执行文件
add_executable(thttpd.out main.cpp http.cpp custom_handle.cpp)

# 链接线程支持库
target_link_libraries(thttpd.out pthread)