cmake_minimum_required(VERSION 3.10)
project(Client)

set(SOURCE_FILES main.cpp chatClient.cpp)
add_executable(chatClient ${SOURCE_FILES})
target_include_directories(chatClient PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
