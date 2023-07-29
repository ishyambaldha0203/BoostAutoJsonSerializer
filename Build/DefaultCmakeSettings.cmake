#
# This module define basic definition common to entire application.
#
cmake_minimum_required(VERSION 3.19.0)

include_guard(GLOBAL)

################################################################################
# CONFIGURATIONS & COMMON INCLUDE PATH
################################################################################

# add the modules to the cmake path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/CmakeModules")

################################################################################
# C++ definitions
################################################################################
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

################################################################################
# Compiler definitions
################################################################################

# Currently it support only gcc. Other compilers can be added as needed.
#
# This are program wide settings. Do not add settings that might be specific to a target.
#

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    ############################################################################
    # Compiler options
    ############################################################################
    # compiler features
    add_compile_options(-fstack-protector-all)

    # Warning definitions
    add_compile_options(-Werror) # convert all the warning as errors
    add_compile_options(-Wall -Wextra -Wpedantic) # https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
    # see https://gcc.gnu.org/onlinedocs/gcc/C_002b_002b-Dialect-Options.html#C_002b_002b-Dialect-Options for other options
    add_compile_options(
        -Wold-style-cast
        -Wnoexcept
        -Wstrict-null-sentinel
        -Wextra-semi
        -Wsuggest-override
        -Wuseless-cast
    )
else()
    message(FATAL_ERROR "compiler not supported")
endif()

################################################################################
# Output
################################################################################
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/exe/${CMAKE_BUILD_TYPE})
