# CMake Version
cmake_minimum_required(VERSION 3.0)

# Constants
set(PROJECT_NAME "sfml-game")

# Project Name
project(${PROJECT_NAME})

# C++ Standard
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
  src/Classes/Item.cpp
  src/Classes/Collisions.cpp
  src/Classes/Block.cpp
  src/Headers/Game.hpp
  src/Headers/Entity.hpp
  src/Headers/Player.hpp
  src/Headers/Manager.hpp
  src/Headers/BackgroundRect.hpp
  src/Headers/Item.hpp
  src/Headers/Collisions.hpp
  src/Headers/Block.hpp
  src/Structs/InventoryItem.hpp
  src/Constants.hpp
)
target_include_directories(${PROJECT_NAME} PUBLIC src)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-audio config++)
