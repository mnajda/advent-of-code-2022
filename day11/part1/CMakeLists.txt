cmake_minimum_required(VERSION 3.4)
project(part1)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES main.cpp)

add_executable(part1 ${SOURCES})

if(MSVC)
    set(RELEASE_OPTIONS "/O2")
    target_compile_options(part1 PRIVATE "/W4" "/permissive-" "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
else()
    target_compile_options(part1 PRIVATE "-O3" "-Wall" "-Wextra" )
endif()
