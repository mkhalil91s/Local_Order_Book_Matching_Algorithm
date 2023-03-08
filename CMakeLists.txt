cmake_minimum_required(VERSION 3.12) # version can be different

set(CMAKE_CXX_STANDARD 17)

project(lob) #name of your project

add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(lobTest 
                ../lob.cpp
                test.cpp) # add this executable

target_link_libraries(lobTest PRIVATE gtest) # link google test to this executable


add_executable(lob2
            ../lob.cpp) # add this executab