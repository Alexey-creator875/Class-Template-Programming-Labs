cmake_minimum_required(VERSION 3.23)

set(project "lab_2")
project(${project})

set(CMAKE_CXX_STANDARD 20)

set(${project}_SOURCES
        main.cpp)

add_subdirectory(Planet)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST})

target_link_libraries(${project} Planet)
#target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)