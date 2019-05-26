cmake_minimum_required(VERSION 3.0.0)
project(idomeres VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable (idomeres main.cpp)
add_custom_command( COMMAND idomeres
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
OUTPUT ${CMAKE_BINARY_DIR}/data.txt
DEPENDS idomeres
COMMENT "Generating data set")
add_custom_target(data ALL DEPENDS ${CMAKE_BINARY_DIR}/data.txt)

set(GNUPLOT_EXECUTABLE "C:\\Program Files\\gnuplot\\bin\\gnuplot.exe")

find_package (Gnuplot REQUIRED)

add_custom_command( COMMAND ${GNUPLOT_EXECUTABLE} ${PROJECT_SOURCE_DIR}/plot.txt
WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
OUTPUT ${CMAKE_BINARY_DIR}/data.png
DEPENDS ${PROJECT_SOURCE_DIR}/plot.txt data
COMMENT "Generating plot")
add_custom_target(plot ALL DEPENDS ${CMAKE_BINARY_DIR}/data.png)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
