CMAKE_MINIMUM_REQUIRED(VERSION 3.15)
PROJECT(cpp-extensions)

SET(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(fail)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")

INCLUDE_DIRECTORIES(../include)

MACRO(TEST name)
	ADD_EXECUTABLE(${name} ${name}.cpp)
ENDMACRO()

ADD_CUSTOM_TARGET(tests)

file(GLOB filenames "*.cpp")

FOREACH(fn ${filenames})
	GET_FILENAME_COMPONENT(name ${fn} NAME_WE)
	TEST(${name})
	ADD_DEPENDENCIES(tests ${name})
ENDFOREACH()
