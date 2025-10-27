cmake_minimum_required(VERSION 3.15)
project(GameEngine2D)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(GameEngine2D ${SOURCES})
target_link_libraries(GameEngine2D ${SDL2_LIBRARIES})
