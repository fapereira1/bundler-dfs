cmake_minimum_required(VERSION 3.20)
project(bundler-dfs VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
  -Wall
  -Wextra
  -Wpedantic
)

set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-g3 -O0)

add_executable(bundler-dfs
  src/main.c
  src/graph/graph.c
  src/algorithms/algorithms.c
  src/parser/parser.c
)

target_include_directories(bundler-dfs PRIVATE src)