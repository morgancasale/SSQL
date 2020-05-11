cmake_minimum_required(VERSION 3.16)
project(CS_Project)

set(CMAKE_CXX_STANDARD 11)

add_executable(CS_Project main.cpp Classes/Time/Time.cpp Classes/Time/Time.h Classes/Date/Date.cpp Classes/Date/Date.h utility.h)
add_executable(CS_Project_meta tests/Metaclass_test.cpp tests/Metaclass.cpp tests/Metaclass.h
        Classes/Time/Time.cpp Classes/Time/Time.h
        Classes/Date/Date.cpp Classes/Date/Date.h
        Classes/Table/Table.cpp Classes/Table/Table.h
        utility.h)