CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(ext)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(ext main.cpp algorithm cstddef memory tuple type_traits utility)
