cmake_minimum_required(VERSION 3.15)
project(PankeyEngineBase)

# Header-only library
add_library(PankeyEngineBase INTERFACE)

# Expose the folder with headers
target_include_directories(PankeyEngineBase INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}   # headers are in the root of ThePankeyEngine-Base
)

