cmake_minimum_required(VERSION 3.22)

project(MYSTICALAND_ECOSYSTEM VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# JUCE Dependency via FetchContent (pinned to JUCE 9.0.5)
include(FetchContent)
FetchContent_Declare(
    JUCE
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        9.0.5
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(JUCE)

# Global compiler settings
if (MSVC)
    add_compile_options(/W4 /WX- /permissive- /utf-8)
endif()

# Include Shared Modules
add_subdirectory(Shared)

# Include Products
add_subdirectory(Products/Shell)
