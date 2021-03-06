include(CheckCSourceCompiles)

function (UC_CHOOSE_C_COMPILER_FLAG FLAG FALLBACK_FLAG RESULT_FLAG)
    if (DEFINED ${RESULT_FLAG})
        return()
    endif()
    message(STATUS "Check if compiler accept ${FLAG}")
    set(CMAKE_REQUIRED_FLAGS ${FLAG})
    set(CMAKE_REQUIRED_QUIET ON)
    unset(UC_HAVE_FLAG CACHE)
    CHECK_C_SOURCE_COMPILES("int main(int argc, char **argv){return 0;}"
     UC_HAVE_FLAG)
    if (${UC_HAVE_FLAG})
        message(STATUS "Check if compiler accept ${FLAG} - yes")
        set(${RESULT_FLAG} ${FLAG} CACHE INTERNAL "")
    else()
        message(STATUS "Check if compiler accept ${FLAG} - no")
        set(${RESULT_FLAG} ${FALLBACK_FLAG} CACHE INTERNAL "")
    endif()
endfunction()
