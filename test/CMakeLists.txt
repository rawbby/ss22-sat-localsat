cmake_minimum_required(VERSION 3.1)

#   ____   _____   _   _   _____   ____    ___    ____
#  / ___| | ____| | \ | | | ____| |  _ \  |_ _|  / ___|
# | |  _  |  _|   |  \| | |  _|   | |_) |  | |  | |
# | |_| | | |___  | |\  | | |___  |  _ <   | |  | |___
#  \____| |_____| |_| \_| |_____| |_| \_\ |___|  \____|

file(GLOB TEST_SOURCE *.cpp)

foreach (TEST_SOURCE ${TEST_SOURCE})

    # create the test name from test file and project name
    get_filename_component(TEST_NAME "${TEST_SOURCE}" NAME_WE)

    # create executable for the test
    add_executable("${TEST_NAME}")
    target_sources("${TEST_NAME}" PRIVATE "${TEST_SOURCE}")
    target_link_libraries("${TEST_NAME}" PRIVATE stl sls)
    set_target_properties("${TEST_NAME}" PROPERTIES
            LINKER_LANGUAGE CXX
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON)

    # register executable as test
    add_test(NAME "${TEST_NAME}" COMMAND $<TARGET_FILE:${TEST_NAME}>)

endforeach ()
