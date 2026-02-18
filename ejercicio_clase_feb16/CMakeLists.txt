cmake_minimum_required(VERSION 3.10)

project(MotionAnalysisOpenCV)

# Usamos C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Buscar OpenCV
find_package(OpenCV REQUIRED)

# Ejecutable: Frame Difference
add_executable(frame_difference
    frame_difference.cpp
)
target_link_libraries(frame_difference ${OpenCV_LIBS})

# Ejecutable: Running Average
add_executable(running_average
    running_average.cpp
)
target_link_libraries(running_average ${OpenCV_LIBS})

# Ejecutable: Background Subtraction (opcional)
add_executable(background_subtraction
    background_subtraction.cpp
)
target_link_libraries(background_subtraction ${OpenCV_LIBS})
