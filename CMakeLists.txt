cmake_minimum_required(VERSION 3.16)
project(loom C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# -----------------------------------------------
# Library: loom
# -----------------------------------------------

add_library(loom
    lib/loom.c
    lib/queue.c
    lib/scheduler.c
    lib/stack.c
    lib/task.c
    asm/context.S
)

# Public include directory
target_include_directories(loom
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/internals
)

target_include_directories(loom
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Enable ASM
enable_language(ASM)

# -----------------------------------------------
# Examples
# -----------------------------------------------

add_executable(basic examples/basic.c)

target_link_libraries(basic PRIVATE loom)

# -----------------------------------------------
# Warnings
# -----------------------------------------------

target_compile_options(loom PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_compile_options(basic PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)