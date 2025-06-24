cmake_minimum_required(VERSION 3.10)
project(brainfC)

set(CMAKE_C_STANDARD 99)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new build directory and run CMake from there.")
endif()

add_executable(${PROJECT_NAME} "stack.c" "brainf.c")

# Unneccessarily aggresive optimization, for fun

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /O3
        /Qspectre
        /EHSc
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -O3
        -s
        -finline-functions
        -funroll-loops
        -flto
        -fomit-frame-pointer
        -fstack-protector-strong
        -march=native
        -g0
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    )