cmake_minimum_required(VERSION 2.6.0)
project(BackPropagation)

add_definitions(-Wall)

set(CMAKE_CXX_FLAGS "-O3 -msse2 -msse3")

FILE(GLOB srcs *.cpp)
source_group("Source Files" FILES ${srcs} )

add_executable(BackPropagation
               ${srcs}
)
