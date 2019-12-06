CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(cpp14)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(cpp14 main.cpp type_traits utility memory algorithm tuple)