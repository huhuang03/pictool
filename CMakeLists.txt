cmake_minimum_required(VERSION 3.12)

project(pic_tool)

FILE(GLOB_RECURSE SRC *.cc *.h *.hpp *.cpp *.c)

find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_executable(pic_tool ${SRC})
