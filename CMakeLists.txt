cmake_minimum_required(VERSION 4.0)
project(Swimming_Card_Management)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(Swimming_Card_Management
        Bill.cpp
        Bill.h
        Card.cpp
        Card.h
        CardManager.cpp
        CardManager.h
        strutil.cpp
        strutil.h
        StudentCard.cpp
        StudentCard.h
        Swimcaco3.cpp
        TeacherCard.cpp
        TeacherCard.h
        timeutil.cpp
        timeutil.h)
