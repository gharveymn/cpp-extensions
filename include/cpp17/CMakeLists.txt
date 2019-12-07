CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(cpp17)

SET(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES("C:\\workspace\\cpp\\llvm-project\\libcxx\\include")

ADD_EXECUTABLE(cpp17 main.cpp cmath cstddef algorithm numeric memory type_traits variant)
