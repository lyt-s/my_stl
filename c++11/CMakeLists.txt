
file(GLOB sources CONFIGURE_DEPENDS *.cpp)
foreach (source IN ITEMS ${sources})
    get_filename_component(name "${source}" NAME_WLE)
    add_executable(${name} ${name}.cpp)
endforeach()

add_executable(test_inline foo.cc test_inline.cc)

target_include_directories(test_inline PUBLIC  ${CMAKE_SOURCE_DIR}/c++17)

# add_executable(test_include test_include.cpp)

# target_include_directories(test_include PUBLIC  ${CMAKE_SOURCE_DIR}/c++17)