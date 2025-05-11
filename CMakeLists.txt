cmake_minimum_required(VERSION 3.23)

set(project "lab_7")
project(${project})

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Executor.cpp)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/Executor.h)

add_subdirectory(MyVector)
add_subdirectory(MechanicalEngineering)

set(SOURCE_LIST
        ${SOURCES}
        ${HEADERS})

add_executable(${project}
        ${SOURCE_LIST})


target_link_libraries(${project} MyVector)
target_link_libraries(${project} MechanicalEngineering)

if(ENABLE_DEBUG)
    target_compile_options(${project} PRIVATE -g)
endif()