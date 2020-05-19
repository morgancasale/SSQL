cmake_minimum_required(VERSION 3.16)
project(CS_Project)

set(CMAKE_CXX_STANDARD 11)

add_executable(CS_Project main.cpp Classes/Database Classes/Date Classes/Time Classes/Table utility.h core.h)
add_executable(CS_Project_meta Classes/Time/Time.cpp Classes/Time/Time.h Classes/Date/Date.cpp Classes/Date/Date.h utility.h)
add_executable(CS_project_test tests/test.cpp utility.h)
