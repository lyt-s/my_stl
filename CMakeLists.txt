
cmake_minimum_required(VERSION 3.18)

if (NOT CMAKE_BUILD_TYPE)
    # set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_BUILD_TYPE Debug)

endif()
set(CMAKE_CXX_STANDARD 20)

##设置 生成compile_commands.json 提供跳转功能 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(stl LANGUAGES CXX)

add_subdirectory(cpplifetimetest)
add_subdirectory(c++20)
add_subdirectory(c++11)
add_subdirectory(c++17)
add_subdirectory(os)
add_subdirectory(stl)
add_subdirectory(leetcode)
add_subdirectory(design)