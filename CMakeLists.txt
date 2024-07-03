cmake_minimum_required(VERSION 3.28)
project(so2_queue_project1)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})

add_executable(so2_queue_project1 main.cpp
        Client.cpp
        Client.h
        Station.cpp
        Station.h
        Coordinates.cpp
        Coordinates.h)

target_link_libraries(so2_queue_project1 ${CURSES_LIBRARIES})
