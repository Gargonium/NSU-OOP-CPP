cmake_minimum_required (VERSION 3.8)
project(lab4)

set(exe_name ${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 17)

add_executable (${PROJECT_NAME} main.cpp  "src/Tuple.cpp" "include/Tuple.h")

target_include_directories(${PROJECT_NAME} PUBLIC "include")
