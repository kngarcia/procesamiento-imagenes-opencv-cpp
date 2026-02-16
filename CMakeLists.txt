cmake_minimum_required(VERSION 3.10)
project(vision_ejercicios)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ej1_rgb_hsv src/ejercicio1.cpp)
add_executable(ej2_saturacion src/ejercicio2.cpp)
add_executable(ej3_kmeans src/ejercicio3.cpp)
add_executable(ej4_gray_world src/ejercicio4.cpp)
add_executable(ej6_gamma src/ejercicio6.cpp)
add_executable(ej7_vignette src/ejercicio7.cpp)

target_link_libraries(ej1_rgb_hsv ${OpenCV_LIBS})
target_link_libraries(ej2_saturacion ${OpenCV_LIBS})
target_link_libraries(ej3_kmeans ${OpenCV_LIBS})
target_link_libraries(ej4_gray_world ${OpenCV_LIBS})
target_link_libraries(ej6_gamma ${OpenCV_LIBS})
target_link_libraries(ej7_vignette ${OpenCV_LIBS})
