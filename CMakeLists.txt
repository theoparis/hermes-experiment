cmake_minimum_required(VERSION 3.23)
project(bruh LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(bruh ./main.cpp)
target_link_libraries(bruh hermes)

