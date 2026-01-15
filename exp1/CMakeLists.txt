cmake_minimum_required(VERSION 3.15...4.0)

project(ShaderExp LANGUAGES C CXX)


# ------------------ Compile with GUI ------------------ #
find_package(raylib)
add_executable(ShaderExp)

target_include_directories(ShaderExp PUBLIC include)

set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

target_link_libraries(ShaderExp raylib)
target_compile_options(ShaderExp PRIVATE -g)


target_sources(ShaderExp PRIVATE
    source/Main.cpp
)