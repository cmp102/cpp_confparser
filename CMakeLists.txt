cmake_minimum_required(VERSION 2.8)

PROJECT(confparser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall --pedantic")

file(GLOB_RECURSE ALLCPP ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${ALLCPP})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
