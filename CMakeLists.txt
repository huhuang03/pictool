cmake_minimum_required(VERSION 3.12)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(pic_tool)


find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_subdirectory(external/easybot)
add_subdirectory(src)

target_link_libraries(pic_tool Qt5::Widgets)