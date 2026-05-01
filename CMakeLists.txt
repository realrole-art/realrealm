cmake_minimum_required(VERSION 3.10)
project(ChatHub)

# On Windows use the GUI frontend; on Unix-like systems build Client/Server
if(WIN32)
    # Build only the Qt GUI client on Windows to avoid POSIX-only sources (e.g. <unistd.h>)
    add_subdirectory(chat_gui_frontend)
    # Ensure MSVC treats source files as UTF-8 to avoid C4819 warnings for non-ASCII comments
    if(MSVC)
        add_compile_options("/utf-8")
    endif()
else()
    # On non-Windows platforms build Client and Server
    add_subdirectory(Client)
    add_subdirectory(Server)
endif()
