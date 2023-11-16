cmake_minimum_required(VERSION 3.0.0)
project(clox++ VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include(CTest)
enable_testing()

add_executable(clox++ main.cpp common.hpp chunk.hpp chunk.cpp debug.cpp value.hpp value.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
