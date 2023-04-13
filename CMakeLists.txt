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
  src/Classes/Entity.cpp
  src/Classes/Player.cpp
  src/Classes/Manager.cpp
  src/Classes/BackgroundRect.cpp
  src/Headers/Game.hpp
  src/Headers/Entity.hpp
  src/Headers/Player.hpp
  src/Headers/Manager.hpp
  src/Headers/BackgroundRect.hpp
)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio config++)
