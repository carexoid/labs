cmake_minimum_required(VERSION 3.17)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)
find_package(Curses REQUIRED)
link_libraries(Threads::Threads ${CURSES_LIBRARIES})

include_directories(src lib ${CURSES_INCLUDE_DIR})
add_executable(lab1 main.cpp)
