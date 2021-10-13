CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(entrega)
set(CMAKE_CXX_STANDARD 11) # C++11,C++14,17,20
FIND_PACKAGE(OpenCV 	REQUIRED )
include_directories ("${OpenCV_INCLUDE_DIRS}")
LINK_LIBRARIES(${OpenCV_LIBS} ${XRAND})

add_executable(ej1 ej1.cpp)
add_executable(prueba2 prueba2.cpp)
