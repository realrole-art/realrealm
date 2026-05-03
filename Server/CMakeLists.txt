cmake_minimum_required(VERSION 3.10)
project(Server)

set(SOURCE_FILES main.cpp chatServer.cpp)
add_executable(chatServer ${SOURCE_FILES})
target_include_directories(chatServer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
