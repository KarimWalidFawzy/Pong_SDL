cmake_minimum_required(VERSION 3.10)
project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/inc)
find_package(SDL3 CONFIG REQUIRED)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/ball.cpp
	src/bat.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
