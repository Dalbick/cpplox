cmake_minimum_required(VERSION 3.0.0)
project(clox++ VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

include(CTest)
enable_testing()

set(FILES common.hpp chunk.hpp chunk.cpp debug.cpp value.hpp value.cpp vm.hpp vm.cpp compiler.hpp compiler.cpp scanner.hpp scanner.cpp)

add_executable(clox++ main.cpp ${FILES})

add_executable(benchmark benchmark.cpp ${FILES})
add_test(NAME benchmark COMMAND benchmark)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
