cmake_minimum_required(VERSION 3.10.0)

set (CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
SET(CMAKE_CXX_FLAGS "-std=c++20")
set(CMAKE_CXX_FLAGS "-O2")


#project name
project (potion)


add_executable(a.out include/http_request.cc include/server.cc include/handler.cc sample_server.cc)