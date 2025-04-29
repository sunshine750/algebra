cmake_minimum_required(VERSION 3.10)

# 项目名称
project(AlgebraProject)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)

# 包含头文件目录
include_directories(inc)

# 添加源文件
set(SOURCES
    src/main.c
    src/algebra.c
)

# 生成可执行文件
add_executable(algebra ${SOURCES})