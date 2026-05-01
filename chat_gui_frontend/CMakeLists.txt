cmake_minimum_required(VERSION 3.16)
project(ChatGuiClient LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Widgets Network REQUIRED)

add_executable(ChatGuiClient
    main_gui.cpp
    chatGuiClient.cpp
    chatGuiClient.h
)

target_link_libraries(ChatGuiClient Qt6::Widgets Qt6::Network)
