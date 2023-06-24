cmake_minimum_required(VERSION 3.7...3.25) # CMake version check

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

include(${CMAKE_SOURCE_DIR}/config.cmake)

project(HasbuEngine VERSION 0.1
    DESCRIPTION "A game engine"
    LANGUAGES CXX)

# Set the C++ standard and require it for all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the C++ compiler and export the compile commands
set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang++)

# set(CMAKE_CXX_COMPILER /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configure options for Debug and Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build: Debug or Release" FORCE)
endif()

# Add specific compile options for Debug and Release modes
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -Og -Wall -Wextra -fno-omit-frame-pointer -fstack-protector)
    add_compile_definitions(DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O3 -march=native -flto)
    add_compile_definitions(RELEASE)
endif()

message("Building in ${CMAKE_BUILD_TYPE} mode")
message("Using compiler: ${CMAKE_CXX_COMPILER}")

# Configure the output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${output_directory})

add_subdirectory(Hasbu)

add_executable(HasbuEngine main.cpp)
target_link_libraries(HasbuEngine PUBLIC HasbuLib)
target_compile_features(HasbuEngine PUBLIC cxx_std_20)
