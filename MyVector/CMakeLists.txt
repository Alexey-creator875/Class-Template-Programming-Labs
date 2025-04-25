cmake_minimum_required(VERSION 3.23)

set(project "MyVector")
project(${project})

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/MyVector.cpp)

set(HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/MyVector.h)

set(SOURCE_LIST
        ${SOURCES}
        ${HEADERS})

add_library(${project} STATIC ${SOURCE_LIST})