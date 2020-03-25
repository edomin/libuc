cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(options)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE
        STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

if(UC_CODE_COVERAGE)
    if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Setting build type to 'Debug' because Code Coverage needs Debug build.")
        set(CMAKE_BUILD_TYPE "Debug")
    endif()
    set(UC_LANGUAGES C CXX)
else()
    set(UC_LANGUAGES C)
endif()

project(uc LANGUAGES ${UC_LANGUAGES})

include(CheckCCompilerFlag)
check_c_compiler_flag("-Walloca" UC_HAVE_WALLOCA)
check_c_compiler_flag("-Wdangling-else" UC_HAVE_WDANGLING_ELSE)
check_c_compiler_flag("-Wduplicated-branches" UC_HAVE_WDUPLICATED_BRANCHES)
check_c_compiler_flag("-Wif-not-aligned" UC_HAVE_WIF_NOT_ALIGNED)
check_c_compiler_flag("-Wstringop-truncation" UC_HAVE_WSTRINGOP_TRUNCATION)
if (UC_HAVE_WALLOCA)
    set(UC_WALLOCA "-Walloca")
else()
    set(UC_WALLOCA "")
endif()
if (UC_HAVE_WDANGLING_ELSE)
    set(UC_WDANGLING_ELSE "-Wdangling-else")
else()
    set(UC_WDANGLING_ELSE "")
endif()
if (UC_HAVE_WDUPLICATED_BRANCHES)
    set(UC_WDUPLICATED_BRANCHES "-Wduplicated-branches")
else()
    set(UC_WDUPLICATED_BRANCHES "")
endif()
if (UC_HAVE_WIF_NOT_ALIGNED)
    set(UC_WIF_NOT_ALIGNED "-Wif-not-aligned")
else()
    set(UC_WIF_NOT_ALIGNED "")
endif()
if (UC_HAVE_WSTRINGOP_TRUNCATION)
    set(UC_WSTRINGOP_TRUNCATION "-Wstringop-truncation")
else()
    set(UC_WSTRINGOP_TRUNCATION "")
endif()

add_library(uc)
set_target_properties(uc PROPERTIES
    C_STANDARD 90
    C_EXTENSIONS OFF
)
target_compile_options(uc PRIVATE
    -Wall -Wextra -Wno-unused-parameter -Wshadow -Werror
)
if (UC_MORE_WARNINGS)
    target_compile_options(uc PRIVATE
        -Waggregate-return ${UC_WALLOCA} -Wbad-function-cast -Wcast-align
        -Wcast-qual ${UC_WDANGLING_ELSE} -Wdeclaration-after-statement
        ${UC_WDUPLICATED_BRANCHES} -Wduplicated-cond ${UC_WIF_NOT_ALIGNED}
        -Winit-self -Winline -Wjump-misses-init -Wlogical-op -Wnested-externs
        -Wnonnull -Wnonnull-compare -Wnull-dereference -Wold-style-definition
        -Wpointer-arith -Wredundant-decls -Wshift-overflow=2
        -Wstrict-prototypes ${UC_WSTRINGOP_TRUNCATION} -Wswitch-default
        -Wswitch-enum -Wundef -Wuninitialized -Wunsafe-loop-optimizations
        -Wvector-operation-performance -Wvla -Wwrite-strings
    )
endif()
target_sources(uc PRIVATE
    "src/uc.c"
)
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
    target_sources(uc PRIVATE "src/uc.rc")
    set(UC_SO_DEST "bin")
else()
    set(UC_SO_DEST "lib")
endif()
target_include_directories(uc PRIVATE include)

set_target_properties(uc PROPERTIES PUBLIC_HEADER "include/uc.h")

if(UC_CODE_COVERAGE)
    include(CodeCoverage)
    APPEND_COVERAGE_COMPILER_FLAGS()
    set(UC_COVERAGE_FLAGS "-fprofile-arcs -ftest-coverage")
    set(COVERAGE_LCOV_EXCLUDES "${CMAKE_SOURCE_DIR}/test/*")

    enable_testing()
    set(UC_TESTS_SOURCES_DIR "test")
    find_package(CMOCKA REQUIRED)

    function(UC_ADD_TEST func)
        set(TEST_NAME "test_${func}")
        add_executable(${TEST_NAME} "${UC_TESTS_SOURCES_DIR}/${func}.c")
        target_include_directories(${TEST_NAME} PRIVATE include)
        target_link_libraries(
            ${TEST_NAME}
            ${CMOCKA_LIBRARY}
            ${UC_COVERAGE_FLAGS}
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
    UC_ADD_TEST(UC_Utf8Copy)
    UC_ADD_TEST(UC_Ucs4ToUtf8)
    UC_ADD_TEST(UC_Utf8ToUcs4)
    UC_ADD_TEST(UC_Ucs4UpperBytes)
    UC_ADD_TEST(UC_Ucs4LowerByte)
    UC_ADD_TEST(UC_StringUtf8NextCodepoint)
    UC_ADD_TEST(UC_StringUtf8NextCodepointOffset)
    UC_ADD_TEST(UC_StringUtf8PreviousCodepoint)
    UC_ADD_TEST(UC_StringUtf8PreviousCodepointOffset)
    UC_ADD_TEST(UC_StringUtf8Codepoints)
    UC_ADD_TEST(UC_StringUtf8Size)
    UC_ADD_TEST(UC_StringUcs4Len)
    UC_ADD_TEST(UC_StringUcs4Size)
    UC_ADD_TEST(UC_StringUcs4PredictUtf8Size)
    UC_ADD_TEST(UC_StringUcs4ToUtf8)
    UC_ADD_TEST(UC_StringUtf8ToUcs4)

    SETUP_TARGET_FOR_COVERAGE_LCOV(
        NAME         test_coverage
        EXECUTABLE   ctest
        DEPENDENCIES uc
    )
else()
    install(
        TARGETS       uc
        RUNTIME       DESTINATION bin
        LIBRARY       DESTINATION ${UC_SO_DEST}
        ARCHIVE       DESTINATION lib
        PUBLIC_HEADER DESTINATION include
    )
endif()
