Cmake_minimum_required(VERSION 2.8)
Project(ConvertDepth)
get_filename_component(PROJECT_ROOT . ABSOLUTE)
# You can prepare verbose Makefile to see what's going.
set(CMAKE_VERBOSE_MAKEFILE false)
# Set build type
set(CMAKE_BUILD_TYPE Debug)

# set the output directory.
SET(OUTPUT ${PROJECT_ROOT}/output CACHE PATH "Path prefix for installation")
SET(CMAKE_BINARY_DIR ${OUTPUT})

include_directories(/usr/include/boost)
find_package(Boost COMPONENTS filesystem REQUIRED)

include_directories(/usr/include/opencv)

add_executable(ConvertDepth ConvertDepth.cpp)
target_link_libraries(ConvertDepth OpenNI)
target_link_libraries(ConvertDepth glut)
target_link_libraries(ConvertDepth cv)
target_link_libraries(ConvertDepth cvaux highgui)
target_link_libraries(ConvertDepth boost_regex boost_filesystem)
install(TARGETS ConvertDepth DESTINATION ${OUTPUT})

