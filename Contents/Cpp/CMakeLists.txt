cmake_minimum_required(VERSION 3.10)
project(HelloC++)

set(CMAKE_CXX_STANDARD 17)

# 将可执行文件命名为 my_first_cplus，并指定正确的源文件路径
# 因为目录 "Lesson 01" 包含空格，所以需要使用引号
add_executable(my_first_cplus "Lesson 01/my_first_cplus.cpp")