CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(cpp14)

SET(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(include)

ADD_EXECUTABLE(is_permutation_pred_test is_permutation_pred_test.cpp)
ADD_EXECUTABLE(is_permutation_test is_permutation_test.cpp)
ADD_EXECUTABLE(mismatch_test mismatch_test.cpp)
ADD_EXECUTABLE(mismatch_pred_test mismatch_pred_test.cpp)
ADD_EXECUTABLE(equal_test equal_test.cpp)
ADD_EXECUTABLE(equal_pred_test equal_pred_test.cpp)
ADD_EXECUTABLE(tuple_test_pass tuple_test_pass.cpp)
ADD_EXECUTABLE(tuple_test_fail tuple_test_fail.cpp)

ADD_EXECUTABLE(cpp14 main.cpp include/cpp14/type_traits include/cpp14/utility include/cpp14/memory include/cpp14/algorithm include/cpp14/tuple)