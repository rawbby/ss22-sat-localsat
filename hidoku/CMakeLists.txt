cmake_minimum_required(VERSION 3.1)

project(hidoku LANGUAGES CXX)

set(TARGET_NAME ${PROJECT_NAME}_solver)
add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE hidoku.cpp)
target_compile_definitions(${TARGET_NAME} PRIVATE SLS_OPTION_SOLVE SLS_OPTION_PAIRWISE)
target_link_libraries(${TARGET_NAME} PRIVATE stl sls)
set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)

set(TARGET_NAME ${PROJECT_NAME}_encoder)
add_executable(${TARGET_NAME})
target_sources(${TARGET_NAME} PRIVATE hidoku.cpp)
target_compile_definitions(${TARGET_NAME} PRIVATE SLS_OPTION_VERBOSE)
target_link_libraries(${TARGET_NAME} PRIVATE stl sls)
set_target_properties(${TARGET_NAME} PROPERTIES
        LINKER_LANGUAGE CXX
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON)
