cmake_minimum_required(VERSION 3.10)
project(HelloC++)

# --- 设置 C++ 标准 ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- 开启跨平台的编译器警告 ---
# 适用于 MSVC、GCC 和 Clang 的警告设置
if(MSVC)
    # MSVC 编译器警告设置
    add_compile_options(/W3)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    # GCC 或 Clang 的警告设置
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- 自动识别源文件路径 ---
# 自动处理包含空格的路径（例如 "Lesson 01"）
file(GLOB_RECURSE SOURCES "Lesson 01/*.cpp")

# --- 添加可执行文件 ---
add_executable(my_first_cplus ${SOURCES})
