cmake_minimum_required(VERSION 3.10)
project( TD CXX C)

set(CMAKE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(httpProxy OBJECT
    src/proxy.cpp
    src/HttpClient.cpp
    src/Request.cpp
    src/Response.cpp
)

add_executable( Proxy main.cpp $<TARGET_OBJECTS:httpProxy> )