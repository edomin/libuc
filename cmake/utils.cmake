# include(CheckCSourceCompiles)

# TODO
function(uc_compiler_flag_supported FLAG RESULT_VAR)
    if (DEFINED ${RESULT_VAR})
        return()
    endif()
    message(STATUS "Check if compiler accept ${FLAG}")
    file(WRITE "${CMAKE_BINARY_DIR}/test.c"
     "int main(int argc, char **argv){return 0;}")
    execute_process(
        COMMAND
            ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${FLAG}
            -c ${CMAKE_BINARY_DIR}/test.c
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE UC_RESULT
        # OUTPUT_VARIABLE UC_OUTPUT
        ERROR_VARIABLE UC_ERROR
    )
    if (UC_RESULT STREQUAL 0)
        string(REGEX MATCH "warning: unsupported option"
            UC_REGEX_MATCH_UNSUPPORTED "${UC_ERROR}") # TCC warning with
                                                      # exitcode 0
        if (NOT UC_REGEX_MATCH_UNSUPPORTED)
            set(UC_HAVE_FLAG 1)
        endif()
    endif()
    if (${UC_HAVE_FLAG})
        message(STATUS "Check if compiler accept ${FLAG} - yes")
        set(${RESULT_FLAG} ${FLAG} CACHE INTERNAL "")
    else()
        message(STATUS "Check if compiler accept ${FLAG} - no")
        set(${RESULT_FLAG} ${FALLBACK_FLAG} CACHE INTERNAL "")
    endif()
endfunction()

function (uc_choose_c_compiler_flag RESULT_FLAG FLAG FALLBACK_FLAG)
    if (DEFINED ${RESULT_FLAG})
        return()
    endif()
    message(STATUS "Check if compiler accept ${FLAG}")
    file(WRITE "${CMAKE_BINARY_DIR}/test.c"
     "int main(int argc, char **argv){return 0;}")
    execute_process(
        COMMAND
            ${CMAKE_C_COMPILER} ${CMAKE_C_FLAGS} ${FLAG}
            -c ${CMAKE_BINARY_DIR}/test.c
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE UC_RESULT
        # OUTPUT_VARIABLE UC_OUTPUT
        ERROR_VARIABLE UC_ERROR
    )
    if (UC_RESULT STREQUAL 0)
        string(REGEX MATCH "warning: unsupported option"
            UC_REGEX_MATCH_UNSUPPORTED "${UC_ERROR}") # TCC warning with
                                                      # exitcode 0
        if (NOT UC_REGEX_MATCH_UNSUPPORTED)
            set(UC_HAVE_FLAG 1)
        endif()
    endif()
    if (${UC_HAVE_FLAG})
        message(STATUS "Check if compiler accept ${FLAG} - yes")
        set(${RESULT_FLAG} ${FLAG} CACHE INTERNAL "")
    else()
        message(STATUS "Check if compiler accept ${FLAG} - no")
        set(${RESULT_FLAG} ${FALLBACK_FLAG} CACHE INTERNAL "")
    endif()
endfunction()
