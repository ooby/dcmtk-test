cmake_minimum_required(VERSION 2.8)

project(test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# specify that we have a config file. This is required, since DCMTK package for Ubuntu 14.04 
# uses /usr/include/dcmtk/config/cfunix.h to setup dcmtk. The file is only loaded by
# DCMTK's /usr/include/dcmtk/config/osconfig.h when HAVE_CONFIG_H is set.
add_definitions(-DHAVE_CONFIG_H)

add_definitions(-DSOURCE_CODE_LOCATION="${CMAKE_SOURCE_DIR}")

set(SOURCE_FILES main.cpp)

find_package(DCMTK REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${DCMTK_INCLUDE_DIRS})

add_executable(test ${SOURCE_FILES})

target_link_libraries(test ${DCMTK_LIBRARIES})
target_link_libraries(test ${OpenCV_LIBS})