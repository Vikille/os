cmake_minimum_required(VERSION 3.10)

project(Lab2_Threads LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Lab2
    src/main.cpp
)

target_include_directories(Lab2 PRIVATE include)

if (WIN32)
    target_link_libraries(Lab2 PRIVATE user32 kernel32)
endif()

add_executable(test
    tests/test.cpp
)

target_include_directories(test PRIVATE include)

if (WIN32)
    target_link_libraries(test PRIVATE user32 kernel32)
endif()
