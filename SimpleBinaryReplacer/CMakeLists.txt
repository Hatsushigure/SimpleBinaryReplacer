cmake_minimum_required(VERSION 3.25)

project(SimpleBinaryReplacer)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB sources ./*.cpp)

add_executable(SimpleBinaryReplacer
    ${sources}
    )