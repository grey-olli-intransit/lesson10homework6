cmake_minimum_required(VERSION 2.8)
add_compile_options(-Wall -g)
project(l10hw7)
add_executable(l10hw7 src/l10hw7.c)
target_include_directories(l10hw7 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(l10hw7 PRIVATE m)

