cmake_minimum_required(VERSION 3.1)

project (sudoku_solver)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /O2 /arch:AVX2")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native")
endif()

set(SOURCES
	src/binsudoku.cpp
	src/example.cpp)

add_executable(example ${SOURCES})

target_include_directories(example
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)