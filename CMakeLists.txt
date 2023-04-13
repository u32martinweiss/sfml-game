# CMake Version
cmake_minimum_required(VERSION 3.0)

# Constants
set(PROJECT_NAME "sfml-game")

# Project Name
project(${PROJECT_NAME})

# C++ Standart
set(CMAKE_CXX_STANDARD 11)

# Packages
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(libconfig++ REQUIRED)

add_executable(
  ${PROJECT_NAME}
  src/Main.cpp
  src/Classes/Game.cpp
  src/Headers/Game.hpp
)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio config++)
