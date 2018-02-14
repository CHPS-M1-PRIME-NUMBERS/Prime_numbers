cmake_minimum_required(VERSION 2.8.12)

project(Prime_numbers_gui LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets)

add_executable(${PROJECT_NAME} "gui.cpp")

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
