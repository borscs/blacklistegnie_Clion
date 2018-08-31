cmake_minimum_required(VERSION 3.1)
project(BlacklistEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core REQUIRED HINTS home/borscs/Qt/5.11.0/gcc_64)
find_package(Qt5Sql REQUIRED HINTS home/borscs/Qt/5.11.0/gcc_64)

include_directories(.)

add_executable(BlacklistEngine jsonfu.h database.h engine.h utils.h handler.h main.cpp handler.cpp engine.cpp utils.cpp database.cpp jsonfu.cpp)

target_link_libraries(BlacklistEngine Qt5::Core Qt5::Sql)