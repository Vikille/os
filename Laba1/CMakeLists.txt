cmake_minimum_required(VERSION 3.10)
project(Lab1Processes LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(creator src/creator.cpp src/employee.cpp)
add_executable(reporter src/reporter.cpp src/employee.cpp)
add_executable(main_app src/main.cpp src/employee.cpp)

enable_testing()
add_executable(test_employee tests/test_employee.cpp src/employee.cpp)
add_test(NAME EmployeeTests COMMAND test_employee)
