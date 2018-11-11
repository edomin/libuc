cmake_minimum_required(VERSION 3.1.3)
project(uconvert)

set(CMAKE_C_STANDARD 90)
set(DEBUG_FLAGS "-O0 -g -ggdb")
set(WARNING_FLAGS "-Wall -Wextra -Werror -Wno-unused-parameter \
 -Wno-unused-but-set-parameter -Winit-self -Wswitch-default \
 -Wduplicated-branches -Wduplicated-cond -Wfloat-equal -Wdangling-else \
 -Wlogical-op")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${DEBUG_FLAGS} ${WARNING_FLAGS}")
set(PROJECT_SOURCES_DIR "src")
set(PROJECT_HEADERS_DIR "include")
include_directories("." "${PROJECT_SOURCES_DIR}" "${PROJECT_HEADERS_DIR}")

list(APPEND SOURCE_FILES
  "${PROJECT_SOURCES_DIR}/uconvert.c"
)

add_library(uconvert ${SOURCE_FILES})

project(test_uconvert)
list(APPEND SOURCE_FILES
  "${PROJECT_SOURCES_DIR}/uconvert.c" "test/test.c"
)
add_executable(test_uconvert ${SOURCE_FILES})
