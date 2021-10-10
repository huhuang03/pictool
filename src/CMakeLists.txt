set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

FILE(GLOB_RECURSE SRC_LIB *.cc *.h *.hpp *.cpp *.c)
list(FILTER SRC_LIB EXCLUDE REGEX ".*main.cc$")

add_library(pictool_lib ${SRC_LIB})

find_package(Qt5 COMPONENTS Widgets REQUIRED)
# fuck, why you can't find the include path?
target_link_libraries(pictool_lib Qt5::Widgets easybot)

add_executable(pictool ${SRC_LIB} main.cc)
# so the link library can pass?
target_link_libraries(pictool pictool_lib)

