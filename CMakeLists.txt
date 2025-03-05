cmake_minimum_required(VERSION 3.23)

set(project "lab_2")
project(${project})

set(CMAKE_CXX_STANDARD 20)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SolarSystem.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ConstructionTeam.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(${project}_SOURCES
        main.cpp
        DataBaseExecutor.cpp)

set(${project}_HEADERS
        DataBaseExecutor.h)

add_subdirectory(Planet)
add_subdirectory(Person)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_executable(${project}
        ${${project}_SOURCE_LIST})

target_link_libraries(${project} Planet)
target_link_libraries(${project} Person)
#target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wpedantic)

if(ENABLE_DEBUG)
    target_compile_options(${project} PRIVATE -g)
endif()