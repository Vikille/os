cmake_minimum_required(VERSION 3.10)

project(Lab3_Markers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab3_Markers
    src/main.cpp
)

target_include_directories(Lab3_Markers PRIVATE include)

add_executable(test_marker
    tests/test_marker.cpp
)

target_include_directories(test_marker PRIVATE include)

if (WIN32)
    target_link_libraries(Lab3_Markers PRIVATE user32 kernel32)
    target_link_libraries(test_marker PRIVATE user32 kernel32)
endif()
