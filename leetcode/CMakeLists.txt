
file(GLOB_RECURSE sources CONFIGURE_DEPENDS *.cpp) # 这里要注意 GLOB 和 GLOB_RECURSE 的区别
foreach (source IN ITEMS ${sources})
    get_filename_component(name "${source}" NAME_WLE)
    add_executable(${name} ${name}.cpp)
endforeach()
