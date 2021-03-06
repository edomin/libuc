cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(options)
include(utils)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE
        STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

if(UC_CODE_COVERAGE)
    if(NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        message(STATUS
         "Setting build type to 'Debug' because Code Coverage needs Debug \
         build.")
        set(CMAKE_BUILD_TYPE "Debug")
    endif()
    set(UC_LANGUAGES C CXX)
else()
    set(UC_LANGUAGES C)
endif()

project(uc LANGUAGES ${UC_LANGUAGES})

file(WRITE "${CMAKE_BINARY_DIR}/dummy.c" "int __unused__;")
add_library(uc_objlib OBJECT "${CMAKE_BINARY_DIR}/dummy.c")
set_target_properties(uc_objlib PROPERTIES
    C_STANDARD 90
    C_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE 1
)
list(APPEND UC_COMPILE_OPTIONS -Wall -Wextra -Wshadow -Werror -fmax-errors=100)
if(UC_WERROR)
    list(APPEND UC_COMPILE_OPTIONS -Werror)
endif()
if(UC_MORE_WARNINGS)
    UC_CHOOSE_C_COMPILER_FLAG("-fanalyzer" "" UC_FANALYZER)
    UC_CHOOSE_C_COMPILER_FLAG("-fanalyzer-verbosity=3" ""
     UC_FANALYZER_VERBOSITY_3)
    UC_CHOOSE_C_COMPILER_FLAG("-Walloca" "" UC_WALLOCA)
    UC_CHOOSE_C_COMPILER_FLAG("-Wanalyzer-too-complex" ""
     UC_WANALYZER_TOO_COMPLEX)
    UC_CHOOSE_C_COMPILER_FLAG("-Wattribute-alias=2" "-Wattribute-alias"
     UC_WATTRIBUTE_ALIAS_2)
    UC_CHOOSE_C_COMPILER_FLAG("-Wc11-c2x-compat" "" UC_WC11_C2X_COMPAT)
    UC_CHOOSE_C_COMPILER_FLAG("-Wdangling-else" "" UC_WDANGLING_ELSE)
    UC_CHOOSE_C_COMPILER_FLAG("-Wduplicated-branches" ""
     UC_WDUPLICATED_BRANCHES)
    UC_CHOOSE_C_COMPILER_FLAG("-Wif-not-aligned" "" UC_WIF_NOT_ALIGNED)
    UC_CHOOSE_C_COMPILER_FLAG("-Wstringop-truncation" ""
     UC_WSTRINGOP_TRUNCATION)
    UC_CHOOSE_C_COMPILER_FLAG("-Wzero-length-bounds" ""
     UC_WZERO_LENGTH_BOUNDS)

    list(APPEND UC_COMPILE_OPTIONS
        ${UC_FANALYZER} ${UC_FANALYZER_VERBOSITY_3} -Waggregate-return
        -Walloc-zero ${UC_WALLOCA} ${UC_WANALYZER_TOO_COMPLEX}
        ${UC_WATTRIBUTE_ALIAS_2} -Wbad-function-cast -Wc++-compat
        ${UC_WC11_C2X_COMPAT} -Wc90-c99-compat -Wc99-c11-compat -Wcast-align
        -Wcast-qual ${UC_WDANGLING_ELSE} -Wdeclaration-after-statement
        -Wdisabled-optimization ${UC_WDUPLICATED_BRANCHES} -Wduplicated-cond
        ${UC_WIF_NOT_ALIGNED} -Wimplicit-fallthrough=5 -Winit-self -Winline
        -Winvalid-pch -Wjump-misses-init -Wlogical-op -Wmissing-include-dirs
        -Wnested-externs -Wnonnull -Wnonnull-compare -Wnull-dereference
        -Wold-style-definition -Wopenmp-simd -Wpointer-arith -Wpedantic
        -Wredundant-decls -Wshift-overflow=2 -Wsign-conversion -Wstack-protector
        -Wstrict-prototypes ${UC_WSTRINGOP_TRUNCATION} -Wswitch-default
        -Wshift-negative-value -Wshift-overflow=2 -Wstrict-overflow=4
        -Wsuggest-attribute=cold -Wsuggest-attribute=const
        -Wsuggest-attribute=malloc -Wsuggest-attribute=noreturn
        -Wsuggest-attribute=pure -Wswitch-default -Wswitch-enum -Wtrampolines
        -Wundef -Wuninitialized -Wunknown-pragmas -Wunsafe-loop-optimizations
        -Wvector-operation-performance -Wvla -Wwrite-strings
        ${UC_WZERO_LENGTH_BOUNDS}
    )
endif()
target_compile_options(uc_objlib PRIVATE ${UC_COMPILE_OPTIONS})
target_sources(uc_objlib PRIVATE
    "src/uc.c"
)
if (CMAKE_SYSTEM_NAME STREQUAL Windows)
    set(UC_SO_DEST "bin")
else()
    set(UC_SO_DEST "lib")
endif()

include(CheckTypeSize)

CHECK_TYPE_SIZE(uint_least24_t UC_SIZEOF_UINT_LEAST24_T LANGUAGE C)
if (NOT ${UC_SIZEOF_UINT_LEAST24_T} STREQUAL "")
    set(UC_HAVE_UINT_LEAST24_T ON)
endif()

configure_file(
    "${CMAKE_SOURCE_DIR}/include/uc/config.h.in"
    "${CMAKE_BINARY_DIR}/include/uc/config.h"
)

target_include_directories(uc_objlib PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_BINARY_DIR}/include"
)

add_library(uc SHARED $<TARGET_OBJECTS:uc_objlib>)
add_library(uc_static STATIC $<TARGET_OBJECTS:uc_objlib>)

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
        target_compile_options(${TEST_NAME} PRIVATE ${UC_COMPILE_OPTIONS})
        target_include_directories(${TEST_NAME} PRIVATE
            "${CMAKE_SOURCE_DIR}/include"
            "${CMAKE_BINARY_DIR}/include"
        )
        target_link_libraries(
            ${TEST_NAME}
            ${CMOCKA_LIBRARY}
            ${UC_COVERAGE_FLAGS}
            uc_static
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
endif()

file(STRINGS "${CMAKE_SOURCE_DIR}/include/uc/uc.h"
 UC_VERSION_MAJOR REGEX "#define UC_VERSION_MAJOR[ ]+[0-9]+")
file(STRINGS "${CMAKE_SOURCE_DIR}/include/uc/uc.h"
 UC_VERSION_MINOR REGEX "#define UC_VERSION_MINOR[ ]+[0-9]+")
file(STRINGS "${CMAKE_SOURCE_DIR}/include/uc/uc.h"
 UC_VERSION_PATCH REGEX "#define UC_VERSION_PATCH[ ]+[0-9]+")
string(REGEX REPLACE "#define UC_VERSION_MAJOR[ ]+([0-9]+)" "\\1"
 UC_VERSION_MAJOR "${UC_VERSION_MAJOR}")
string(REGEX REPLACE "#define UC_VERSION_MINOR[ ]+([0-9]+)" "\\1"
 UC_VERSION_MINOR "${UC_VERSION_MINOR}")
string(REGEX REPLACE "#define UC_VERSION_PATCH[ ]+([0-9]+)" "\\1"
 UC_VERSION_PATCH "${UC_VERSION_PATCH}")

if(UC_BUILD_DOC)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        configure_file(
            "${CMAKE_SOURCE_DIR}/Doxyfile.in"
            "${CMAKE_BINARY_DIR}/Doxyfile"
            @ONLY
        )
        add_custom_target(doc ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    else()
        message(
         "Doxygen need to be installed to generate the doxygen documentation"
        )
    endif()
endif()

configure_file(
    "${CMAKE_SOURCE_DIR}/libuc.pc.in"
    "${CMAKE_BINARY_DIR}/libuc.pc"
    @ONLY
)

install(
    FILES "${CMAKE_BINARY_DIR}/libuc.pc"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
)

install(
    TARGETS       uc
    EXPORT        libucConfig
    RUNTIME       DESTINATION bin
    LIBRARY       DESTINATION ${UC_SO_DEST}
    ARCHIVE       DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

install(
    TARGETS       uc_static
    EXPORT        libucConfig
    RUNTIME       DESTINATION bin
    LIBRARY       DESTINATION ${UC_SO_DEST}
    ARCHIVE       DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

export(TARGETS uc uc_static
    NAMESPACE UC::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/libucConfig.cmake"
)

install(EXPORT libucConfig
    DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/libuc"
    NAMESPACE UC::
)
