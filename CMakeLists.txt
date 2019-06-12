#
# Created by jprolejko on 26.02.19.
#

cmake_minimum_required(VERSION 2.6)
project(Gravity)

include_directories(.)
include_directories(include)

set(CMAKE_CXX_STANDARD 14)

# Define sources and executable
set(EXECUTABLE_NAME "Gravity")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/build")

file(GLOB_RECURSE GRAVITY_MAIN_SRC "src/*.cpp")

add_executable(${EXECUTABLE_NAME} ${GRAVITY_MAIN_SRC})

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED COMPONENTS network audio graphics window system)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})


