set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

FILE(GLOB_RECURSE SRC_LIB *.cc *.h *.hpp *.cpp *.c)
list(FILTER SRC_LIB EXCLUDE REGEX ".*main.cc$")

add_library(pictool_lib ${SRC_LIB})

find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(pictool_lib Qt5::Widgets)

add_executable(pictool ${SRC_LIB} main.cc)
