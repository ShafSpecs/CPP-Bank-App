cmake_minimum_required(VERSION 3.28)
project(Bank)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bank main.cpp
        Account.cpp
        Account.h
)
