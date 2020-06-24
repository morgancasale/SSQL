cmake_minimum_required(VERSION 3.16)
project(CS_Project)

set(CMAKE_CXX_STANDARD 11)

add_executable(CS_Project main.cpp
        Classes/Database/Database.h Classes/Database/Database.cpp
        Classes/Table/Table.h Classes/Table/Table.cpp syntax.h
        utility.h Classes/Date/Date.h Classes/Date/Date.cpp
        Classes/Time/Time.h Classes/Time/Time.cpp core.h)

add_executable(CS_Project_meta Classes/Time/Time.cpp Classes/Time/Time.h Classes/Date/Date.cpp Classes/Date/Date.h utility.h)
add_executable(CS_project_test tests/test.cpp)
add_executable(CS_project_test2 tests/test2.cpp)
add_executable(CS_project_test3 tests/test3.cpp)