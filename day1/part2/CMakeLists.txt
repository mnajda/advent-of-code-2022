cmake_minimum_required(VERSION 3.4)
project(part2)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES main.cpp)

add_executable(part2 ${SOURCES})

if(MSVC)
    set(RELEASE_OPTIONS "/O2")
    target_compile_options(part2 PRIVATE "/W4" "/permissive-" "$<$<CONFIG:RELEASE>:${RELEASE_OPTIONS}>")
else()
    target_compile_options(part2 PRIVATE "-O3" "-Wall" "-Wextra" )
endif()
