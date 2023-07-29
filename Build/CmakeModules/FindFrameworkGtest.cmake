#
# Include this module to use gtest in the application source tree.
#

include_guard(GLOBAL)

############################################################################
# FETCH GTEST SOURCE
############################################################################
include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)

FetchContent_MakeAvailable(googletest)

############################################################################
# LIBRARIES
############################################################################

# Since we are compiling gtest with the build, need to change the compiler settings to be less restrictive.
set(GTEST_TARGETS "gtest" "gmock" "gtest_main")

# Need to use the real target here.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    foreach(GTEST_TARGETS_LIB ${GTEST_TARGETS})
        target_compile_options(${GTEST_TARGETS_LIB} PRIVATE -Wno-suggest-override -Wno-useless-cast -Wno-zero-as-null-pointer-constant)
    endforeach()
endif()

add_library(framework::gtest ALIAS gtest)
add_library(framework::gmock ALIAS gmock)
add_library(framework::gtest_main ALIAS gtest_main)

add_library(gtest_suite INTERFACE)
target_link_libraries(gtest_suite INTERFACE
    framework::gtest
    framework::gmock
    framework::gtest_main)
add_library(framework::gtest_suite ALIAS gtest_suite)

# These allow us to use "gtest_discover_tests()" and run `ctest` directly.
include (CTest)
include (GoogleTest)
