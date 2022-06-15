cmake_minimum_required(VERSION 3.22)

project(stl LANGUAGES CXX)

find_package(OpenMP REQUIRED)

add_executable(stl main.cpp)
target_include_directories(stl PRIVATE .)
target_link_libraries(stl PRIVATE OpenMP::OpenMP_CXX)
set_target_properties(stl PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME hidoku_encoder)
add_executable(${TARGET_NAME} hidoku/hidoku_encoder.cpp sokuban/sokuban.cpp)
target_include_directories(${TARGET_NAME} PRIVATE .)
target_link_libraries(${TARGET_NAME} PRIVATE OpenMP::OpenMP_CXX)
set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME hidoku_solver)
add_executable(${TARGET_NAME} hidoku/hidoku_solver.cpp)
target_include_directories(${TARGET_NAME} PRIVATE .)
target_link_libraries(${TARGET_NAME} PRIVATE OpenMP::OpenMP_CXX)
set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)
