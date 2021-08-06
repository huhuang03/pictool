cmake_minimum_required(VERSION 3.12)

project(pic_tool)

FILE(GLOB_RECURSE SRC src/*.cc src/*.h src/*.hpp src/*.cpp src/*.c)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(pic_tool ${SRC})

target_link_libraries(pic_tool Qt5::Widgets)