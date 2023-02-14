cmake_minimum_required(VERSION 3.24)
project(WindowsReadMediaInfo)

set(CMAKE_CXX_STANDARD 17)

add_executable(WindowsReadMediaInfo main.cpp)
set_target_properties(WindowsReadMediaInfo PROPERTIES VS_WINRT_COMPONENT TRUE)
target_link_libraries(WindowsReadMediaInfo WindowsApp.lib)
