cmake_minimum_required(VERSION 3.14)
project(LogisticsOptimizer VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Источники
file(GLOB_RECURSE CORE_SRC "src/core/*.cpp")
file(GLOB_RECURSE IO_SRC "src/io/*.cpp")
file(GLOB_RECURSE CLI_SRC "src/cli/*.cpp")

# Основная программа
add_executable(${PROJECT_NAME} ${CORE_SRC} ${IO_SRC} ${CLI_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Тесты
option(BUILD_TESTS "Build Google Tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
