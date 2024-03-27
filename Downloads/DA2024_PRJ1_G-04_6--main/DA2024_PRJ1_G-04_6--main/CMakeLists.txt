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
        Code/src/main.cpp
        Code/headers/WaterSystem.h
        Code/src/Reservoir.cpp
        Code/headers/Reservoir.h
        Code/src/PumpingStation.cpp
        Code/headers/PumpingStation.h
        Code/src/City.cpp
        Code/headers/City.h
        Code/src/Pipe.cpp
        Code/headers/Pipe.h
        Code/headers/WaterInfrastructure.h
        Code/src/Script.cpp
        Code/headers/Script.h
)
