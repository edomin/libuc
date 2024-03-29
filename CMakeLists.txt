cmake_minimum_required(VERSION 3.11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${BB_MODULE_PATH})

option(UC_BUILD_DOC "Build documentation" OFF)

include(barebones/barebones)

project(uc LANGUAGES C)

bb_add_compile_options(LANG C OPTIONS C_COMPILE_OPTIONS)
bb_add_more_warnings(
    LANG C
    CATEGORIES
        basic
        asciiz
        array
        c89
        documentation
        preprocessor
    OPTIONS C_COMPILE_OPTIONS
)

bb_add_library(uc_objlib OBJECT)
set_target_properties(uc_objlib PROPERTIES
    C_STANDARD 90
    C_EXTENSIONS OFF
    POSITION_INDEPENDENT_CODE 1
)

target_compile_options(uc_objlib PRIVATE ${C_COMPILE_OPTIONS})
target_sources(uc_objlib PRIVATE
    "src/uc.c"
)

bb_process_type_availability(
    LANG C
    TYPE uint_least24_t
    HEADERS stdint.h stddef.h
    WHERE UC_UINT_LEAST24_T_HEADER
)

if(UC_UINT_LEAST24_T_HEADER)
    set(UC_HAVE_UINT_LEAST24_T)
endif()

configure_file(
    "${CMAKE_SOURCE_DIR}/include/uc/config.h.in"
    "${CMAKE_BINARY_DIR}/include/uc/config.h"
)

target_include_directories(uc_objlib PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_BINARY_DIR}/include"
)

list(APPEND UC_TARGETS uc_static)
if (${CMAKE_TRY_COMPILE_TARGET_TYPE} STREQUAL EXECUTABLE)
    list(APPEND UC_TARGETS uc)
    bb_add_library(uc SHARED OBJLIB uc_objlib)
    set_target_properties(uc PROPERTIES PUBLIC_HEADER "include/uc/uc.h")

    set(UC_TARGET uc)
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
        LIBRARY       DESTINATION ${BB_SO_DEST}
        ARCHIVE       DESTINATION lib
        PUBLIC_HEADER DESTINATION include
    )
endif()

bb_add_library(uc_static STATIC OBJLIB uc_objlib)

set_target_properties(uc_static PROPERTIES PUBLIC_HEADER "include/uc/uc.h")

set(UC_TARGET uc_static)
configure_file(
    "${CMAKE_SOURCE_DIR}/libuc.pc.in"
    "${CMAKE_BINARY_DIR}/libuc-static.pc"
    @ONLY
)

install(
    FILES "${CMAKE_BINARY_DIR}/libuc-static.pc"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig
)

install(
    TARGETS       uc_static
    EXPORT        libucConfig
    RUNTIME       DESTINATION bin
    LIBRARY       DESTINATION ${BB_SO_DEST}
    ARCHIVE       DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

export(TARGETS ${UC_TARGETS}
    NAMESPACE UC::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/libucConfig.cmake"
)

install(EXPORT libucConfig
    DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/libuc"
    NAMESPACE UC::
)

bb_test_c_compile_options(${C_COMPILE_OPTIONS})
bb_test_include_directories("${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_BINARY_DIR}/include"
)
bb_test_link_libraries(uc_static)

bb_add_test(UC_GetLinkedVersion
    "${CMAKE_SOURCE_DIR}/test/UC_GetLinkedVersion.c")
bb_add_test(UC_GetLinkedVersionString
    "${CMAKE_SOURCE_DIR}/test/UC_GetLinkedVersionString.c")
bb_add_test(UC_Utf8Size "${CMAKE_SOURCE_DIR}/test/UC_Utf8Size.c")
bb_add_test(UC_Utf8Copy "${CMAKE_SOURCE_DIR}/test/UC_Utf8Copy.c")
bb_add_test(UC_Ucs2ToUtf8 "${CMAKE_SOURCE_DIR}/test/UC_Ucs2ToUtf8.c")
bb_add_test(UC_Ucs4ToUtf8 "${CMAKE_SOURCE_DIR}/test/UC_Ucs4ToUtf8.c")
bb_add_test(UC_Utf8ToUcs2 "${CMAKE_SOURCE_DIR}/test/UC_Utf8ToUcs2.c")
bb_add_test(UC_Utf8ToUcs4 "${CMAKE_SOURCE_DIR}/test/UC_Utf8ToUcs4.c")
bb_add_test(UC_Ucs4UpperBytes "${CMAKE_SOURCE_DIR}/test/UC_Ucs4UpperBytes.c")
bb_add_test(UC_Ucs4LowerByte "${CMAKE_SOURCE_DIR}/test/UC_Ucs4LowerByte.c")
bb_add_test(UC_StringUtf8NextCodepoint
    "${CMAKE_SOURCE_DIR}/test/UC_StringUtf8NextCodepoint.c")
bb_add_test(UC_StringUtf8NextCodepointOffset
    "${CMAKE_SOURCE_DIR}/test/UC_StringUtf8NextCodepointOffset.c")
bb_add_test(UC_StringUtf8PreviousCodepoint
    "${CMAKE_SOURCE_DIR}/test/UC_StringUtf8PreviousCodepoint.c")
bb_add_test(UC_StringUtf8PreviousCodepointOffset
    "${CMAKE_SOURCE_DIR}/test/UC_StringUtf8PreviousCodepointOffset.c")
bb_add_test(UC_StringUtf8Codepoints
    "${CMAKE_SOURCE_DIR}/test/UC_StringUtf8Codepoints.c")
bb_add_test(UC_StringUtf8Size "${CMAKE_SOURCE_DIR}/test/UC_StringUtf8Size.c")
bb_add_test(UC_StringUcs2Len "${CMAKE_SOURCE_DIR}/test/UC_StringUcs2Len.c")
bb_add_test(UC_StringUcs4Len "${CMAKE_SOURCE_DIR}/test/UC_StringUcs4Len.c")
bb_add_test(UC_StringUcs2Size "${CMAKE_SOURCE_DIR}/test/UC_StringUcs2Size.c")
bb_add_test(UC_StringUcs4Size "${CMAKE_SOURCE_DIR}/test/UC_StringUcs4Size.c")
bb_add_test(UC_StringUcs2PredictUtf8Size
    "${CMAKE_SOURCE_DIR}/test/UC_StringUcs2PredictUtf8Size.c")
bb_add_test(UC_StringUcs4PredictUtf8Size
    "${CMAKE_SOURCE_DIR}/test/UC_StringUcs4PredictUtf8Size.c")
bb_add_test(UC_StringUcs2ToUtf8
    "${CMAKE_SOURCE_DIR}/test/UC_StringUcs2ToUtf8.c")
bb_add_test(UC_StringUcs4ToUtf8
    "${CMAKE_SOURCE_DIR}/test/UC_StringUcs4ToUtf8.c")
bb_add_test(UC_StringUtf8ToUcs2
    "${CMAKE_SOURCE_DIR}/test/UC_StringUtf8ToUcs2.c")
bb_add_test(UC_StringUtf8ToUcs4
    "${CMAKE_SOURCE_DIR}/test/UC_StringUtf8ToUcs4.c")

bb_add_coverage(${BB_COVERAGE_TARGET}
    EXCLUDE "${CMAKE_SOURCE_DIR}/test/*"
    DEPS uc_static
)

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
         "Doxygen need to be installed to generate a doxygen documentation"
        )
    endif()
endif()
