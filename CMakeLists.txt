cmake_minimum_required (VERSION 2.8)

SET(NAME "ELF-Parser")
project (${NAME})

SET(CMAKE_CXX_FLAGS "-pedantic -Wall")

MESSAGE(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
# Grab all of the CPP files in src and subdirectories; store in CPP_SRCS
FILE(GLOB_RECURSE CPP_SRCS src/*.cpp)
# Do the same for the headers.
FILE(GLOB_RECURSE CPP_HDRS src/*.hpp)

ADD_EXECUTABLE(${NAME}.bin ${CPP_SRCS} ${CPP_HDRS})
