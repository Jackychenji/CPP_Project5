cmake_minimum_required(VERSION 3.12)

add_definitions(-DWITH_AVX2)

set(CMAKE_C_STANDARD 11)

project(matrix)

add_compile_options(-mfma -fopenmp -mavx2 -O3 )


add_executable(matrix  DefineMatrix.hpp test.cpp)

find_package(OpenMP)
if(OpenMP_C_FOUND)
    message("OpenMP found.")
    target_link_libraries(matrix PUBLIC OpenMP::OpenMP_C)
endif()