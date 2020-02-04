#
# Created by jprolejko on 26.02.19.
#

cmake_minimum_required(VERSION 3.6)
project(Gravity)

set(CMAKE_CXX_STANDARD 14)

# Change this if you're working on Windows to your SFML and TGUI path.
set(SFML_ROOT "C:/SFML-2.5.1")
set(TGUI_ROOT "C:/TGUI-0.8")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)
find_package(TGUI 0.8 REQUIRED)

include_directories(.)
include_directories(include)
include_directories(${SFML_INCLUDE_DIR} ${TGUI_INCLUDE_DIR})

# Define sources and executable
set(EXECUTABLE_NAME "Gravity")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build")

file(GLOB_RECURSE GRAVITY_MAIN_SRC "src/*.cpp")

add_executable(${EXECUTABLE_NAME} ${GRAVITY_MAIN_SRC})

target_link_libraries(${EXECUTABLE_NAME} stdc++fs)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${TGUI_LIBRARY})



