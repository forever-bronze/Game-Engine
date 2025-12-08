cmake_minimum_required(VERSION 3.15)
project(GameEngine2D)

set(CMAKE_CXX_STANDARD 20)

# Enable better package finding
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB SOURCES "src/*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SDL2 with error handling
find_package(SDL2 REQUIRED)
if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 not found! Please install SDL2 development packages.")
endif()

# Find fmt with multiple fallback strategies
find_package(fmt QUIET)

if(NOT fmt_FOUND)
    # Try alternative names
    find_package(FMT QUIET)
    if(NOT FMT_FOUND)
        # Try pkg-config as fallback
        find_package(PkgConfig QUIET)
        if(PKG_CONFIG_FOUND)
            pkg_check_modules(FMT fmt)
            if(FMT_FOUND)
                message(STATUS "Found fmt via pkg-config")
                set(fmt_FOUND TRUE)
            endif()
        endif()
    else()
        set(fmt_FOUND TRUE)
    endif()
endif()

if(NOT fmt_FOUND)
    message(FATAL_ERROR "fmt library not found! Install with: sudo apt install libfmt-dev or build from source")
endif()

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(GameEngine2D ${SOURCES})

# Link with proper error handling
if(fmt_FOUND)
    if(TARGET fmt::fmt)
        target_link_libraries(GameEngine2D ${SDL2_LIBRARIES} SDL2_image SDL2_ttf fmt::fmt)
    elseif(TARGET fmt)
        target_link_libraries(GameEngine2D ${SDL2_LIBRARIES} SDL2_image SDL2_ttf fmt)
    else()
        target_link_libraries(GameEngine2D ${SDL2_LIBRARIES} SDL2_image SDL2_ttf ${FMT_LIBRARIES})
        include_directories(${FMT_INCLUDE_DIRS})
    endif()
    message(STATUS "Linked with fmt library")
endif()
