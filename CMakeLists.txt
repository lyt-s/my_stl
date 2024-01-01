
cmake_minimum_required(VERSION 3.18)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_STANDARD 20)

##设置 生成compile_commands.json 提供跳转功能 
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(stl LANGUAGES CXX)

file(GLOB sources CONFIGURE_DEPENDS *.cpp)
foreach (source IN ITEMS ${sources})
    get_filename_component(name "${source}" NAME_WLE)
    add_executable(${name} ${name}.cpp)
endforeach()


add_executable(test_inline foo.cc test_inline.cc)
add_subdirectory(cpplifetimetest)