cmake_minimum_required(VERSION 3.10)
project( TD CXX C)

set(CMAKE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(httputils OBJECT src/httputils.cpp src/proxy.cpp)

add_executable( Proxy src/main.cpp $<TARGET_OBJECTS:httputils> )
#target_link_libraries(Proxy httputils proxy)