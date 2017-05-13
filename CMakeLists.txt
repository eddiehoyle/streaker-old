cmake_minimum_required(VERSION 3.5)
project(streaker)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(STREAKER_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(STREAKER_INCLUDE_DIR ${STREAKER_ROOT_DIR}/include)
set(STREAKER_SRC_DIR ${STREAKER_ROOT_DIR}/src)
set(STREAKER_PYSRC_DIR ${STREAKER_ROOT_DIR}/src/pystreak)
set(STREAKER_LIB_DIR ${STREAKER_ROOT_DIR}/lib)
set(STREAKER_BIN_DIR ${STREAKER_ROOT_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${STREAKER_LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${STREAKER_LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${STREAKER_BIN_DIR})

# Make a .so output!
if(APPLE)
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
endif(APPLE)

find_package(Boost 1.45.0 COMPONENTS filesystem regex )
#find_package(Boost 1.45.0 COMPONENTS filesystem regex python )
find_package(PythonLibs 2.7 REQUIRED)

add_subdirectory(${STREAKER_SRC_DIR})

# Python wrapper
#add_subdirectory(${STREAKER_PYSRC_DIR})
