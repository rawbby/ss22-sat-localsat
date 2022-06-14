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

add_executable(hidoku hidoku.cpp)
target_include_directories(hidoku PRIVATE .)
target_link_libraries(hidoku PRIVATE OpenMP::OpenMP_CXX)
set_target_properties(hidoku PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)
