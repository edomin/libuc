cmake_minimum_required(VERSION 3.1.3)
project(uc)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

option(BUILD_TESTS "Build test programs" OFF)
option(TEST_CODE_COVERAGE "Test coverage" OFF)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(BUILD_TESTS)
        message(WARNING "Debug build required for building tests. BUILD_TESTS changed to OFF")
        set(BUILD_TESTS OFF)
    endif(BUILD_TESTS)
    if(TEST_CODE_COVERAGE)
        message(WARNING "Debug build required for testing coverage. TEST_CODE_COVERAGE changed to OFF")
        set(TEST_CODE_COVERAGE OFF)
    endif(TEST_CODE_COVERAGE)
endif(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")

if(TEST_CODE_COVERAGE)
    if(NOT BUILD_TESTS)
        message(STATUS "Testing coverage required building tests. BUILD_TESTS changed to ON")
        set(BUILD_TESTS ON)
    endif(NOT BUILD_TESTS)
endif(TEST_CODE_COVERAGE)

set(CMAKE_C_STANDARD 90)
set(DEBUG_FLAGS "-O0 -g -ggdb")
set(WARNING_FLAGS "-Wall -Wextra -Werror -Wno-unused-parameter \
 -Wno-unused-but-set-parameter -Winit-self -Wswitch-default \
 -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wdangling-else \
 -Wlogical-op")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_FLAGS} ${WARNING_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${WARNING_FLAGS}")
set(PROJECT_SOURCES_DIR "src")
set(PROJECT_HEADERS_DIR "include")
include_directories("." "${PROJECT_SOURCES_DIR}" "${PROJECT_HEADERS_DIR}")

list(APPEND SOURCE_FILES
  "${PROJECT_SOURCES_DIR}/uc.c"
)

add_library(uc ${SOURCE_FILES})
set_target_properties(uc PROPERTIES PUBLIC_HEADER "${PROJECT_HEADERS_DIR}/uc.h")

install(
    TARGETS       uc
    RUNTIME       DESTINATION bin
    LIBRARY       DESTINATION lib
    ARCHIVE       DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

if(TEST_CODE_COVERAGE)
    INCLUDE(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    set(COVERAGE_FLAGS "-fprofile-arcs -ftest-coverage")
endif(TEST_CODE_COVERAGE)

if(BUILD_TESTS)
    enable_testing()
    set(TESTS_SOURCES_DIR "test")
    find_package(CMOCKA REQUIRED)

    function(UC_ADD_TEST func)
        set(TEST_NAME "test_${func}")
        add_executable(${TEST_NAME} "${TESTS_SOURCES_DIR}/${func}.c")
        target_link_libraries(
            ${TEST_NAME}
            ${CMOCKA_LIBRARY}
            ${COVERAGE_FLAGS}
            uc
        )
        add_test(
            NAME    ${TEST_NAME}
            COMMAND ./${TEST_NAME}
        )
    endfunction()

    UC_ADD_TEST(UC_GetLinkedVersion)
    UC_ADD_TEST(UC_GetLinkedVersionString)
    UC_ADD_TEST(UC_Utf8Size)
    UC_ADD_TEST(UC_CreateUtf8)
    UC_ADD_TEST(UC_Utf8Copy)
    UC_ADD_TEST(UC_CreateUtf8FromChar)
    UC_ADD_TEST(UC_DeleteUtf8)
    UC_ADD_TEST(UC_Ucs4ToUtf8)
endif(BUILD_TESTS)

if(TEST_CODE_COVERAGE)
    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME         test_coverage
        EXECUTABLE   ctest
        DEPENDENCIES uc
    )
endif(TEST_CODE_COVERAGE)
