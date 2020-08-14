cmake_minimum_required(VERSION 3.0.0)
project(ex1 VERSION 0.1.0)

# include(CTest)
# enable_testing()

set(C_STANDARD C99)
add_library(matrix SHARED ErrorCode.c Matrix.c)
add_compile_options(-Wall -Wextra -pedantic -Werror)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# cmake_minimum_required(VERSION 3.0.0)
# project(matrix VERSION 0.1.0)

# include(CTest)
# set(C_STANDARD C99)
# add_compile_options(-Wall -Wextra -pedantic -Werror)
# enable_testing()

# # Add the libmatrix file to the include path - so that
# #   we can include it as without explicitly specifying 
# #   the files directory.
# include_directories(${CMAKE_SOURCE_DIR}/matrix)
# # Link directories - tells the linker to look for .so files
# #   in these directories. We want libmatrix.so which is under 
# #   the matrix directory. Note that a full path is required.
# link_directories(${CMAKE_SOURCE_DIR}/matrix)
# add_library(libmatrix ErrorCode.c Matrix.c)
# # Links out executable with matrix. ld (the linker) will automatically
# #   add the 'lib' prefix and 'so' suffix, which will result in libmatrix.so
# # target_link_libraries(tester matrix)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
