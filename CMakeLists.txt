cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME "sfml-game")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(${PROJECT_NAME} src/Main.cpp)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
