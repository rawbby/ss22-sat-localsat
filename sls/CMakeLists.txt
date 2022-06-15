cmake_minimum_required(VERSION 3.1)

project(sls LANGUAGES CXX)
find_package(OpenMP REQUIRED)

file(GLOB_RECURSE PROJECT_HEADER *.hpp)
file(GLOB_RECURSE PROJECT_INLINE *.inl)

add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${PROJECT_HEADER})
target_sources(${PROJECT_NAME} INTERFACE ${PROJECT_INLINE})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} INTERFACE stl OpenMP::OpenMP_CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME ${PROJECT_NAME}cli)
add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE main.cpp)
target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${TARGET_NAME} PRIVATE sls)
set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)
