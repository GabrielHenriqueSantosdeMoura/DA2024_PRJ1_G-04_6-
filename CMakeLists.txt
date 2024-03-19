cmake_minimum_required(VERSION 3.26)
project(DA2024_PRJ1_G_04_6_)

set(CMAKE_CXX_STANDARD 14)

include_directories(Code)

add_executable(DA2024_PRJ1_G_04_6_
        Code/headers/Graph.h
        Code/src/Menu.cpp
        Code/headers/Menu.h
        Code/src/DataReader.cpp
        Code/headers/DataReader.h
        Code/src/Script.cpp
        Code/headers/Script.h
        Code/src/main.cpp
        Code/src/WaterSystem.cpp
        Code/headers/WaterSystem.h
        Code/src/Reservoir.cpp
        Code/src/Reservoir.h)
