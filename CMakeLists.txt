cmake_minimum_required(VERSION 3.23)

set(project "lab_3")
project(${project})

set(CMAKE_CXX_STANDARD 20)

set(${project}_SOURCES
        main.cpp)

add_subdirectory(Fraction)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_executable(${project}
        ${${project}_SOURCE_LIST})

target_link_libraries(${project} Fraction)

if(ENABLE_DEBUG)
    target_compile_options(${project} PRIVATE -g)
endif()