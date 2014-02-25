cmake_minimum_required (VERSION 2.8)

SET(ARCH "unknown")
SET(NAME "ELF-Parser")
project (${NAME})

SET(CMAKE_CXX_FLAGS "-pedantic -Wall")

IF(UNIX)
	EXECUTE_PROCESS(COMMAND arch OUTPUT_VARIABLE ARCH)
	STRING(STRIP ${ARCH} ARCH)
	MESSAGE("Building for arch: ${ARCH}")
ENDIF(UNIX)
IF(W32)
	SET(ARCH "w32")
ENDIF(W32)

MESSAGE(STATUS "CXX Flags: " ${CMAKE_CXX_FLAGS})
# Grab all of the CPP files in src and subdirectories; store in CPP_SRCS
FILE(GLOB_RECURSE CPP_SRCS src/*.cpp)
# Do the same for the headers.
FILE(GLOB_RECURSE CPP_HDRS src/*.hpp)

ADD_EXECUTABLE(${NAME}.bin.${ARCH} ${CPP_SRCS} ${CPP_HDRS})
