cmake_minimum_required(VERSION 3.1)

project(monogram LANGUAGES CXX)

set(TARGET_NAME ${PROJECT_NAME}_encoder)
add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE encoder.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE stl sls)
set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME ${PROJECT_NAME}_decoder)
add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE decoder.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE stl sls)
set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)
