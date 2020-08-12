cmake_minimum_required(VERSION 3.0.0)
project(ex1 VERSION 0.1.0)

include(CTest)
enable_testing()

set(C_STANDARD C99)
add_library(ex1 ErrorCode.c Matrix.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
