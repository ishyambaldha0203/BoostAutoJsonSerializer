#
# This is a CMake project file for unit tests boost auto json serilizer library.
cmake_minimum_required(VERSION 3.17.0)

project(BoostJsonSerializer VERSION 0.0.0.1 LANGUAGES CXX)

################################################################
# Configurations
################################################################
include(${CMAKE_CURRENT_SOURCE_DIR}/../Build/DefaultCmakeSettings.cmake)

################################################################################
# VARIABLES
################################################################################
set(BOOST_JSON_SERIALIZER_TEST_TARGET_NAME ${PROJECT_NAME})

set(BOOST_JSON_SERIALIZER_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Src")
set(BOOST_JSON_SERIALIZER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../Include")
set(BOOST_JSON_SERIALIZER_TEST_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Src")

################################################################################
# Dependencies
################################################################################
find_package(FrameworkGtest)
find_package(Boost REQUIRED COMPONENTS json)

################################################################################
# Targets
################################################################################
add_executable(${BOOST_JSON_SERIALIZER_TEST_TARGET_NAME})
add_subdirectory("${BOOST_JSON_SERIALIZER_TEST_SOURCE_DIR}")

target_include_directories(${BOOST_JSON_SERIALIZER_TEST_TARGET_NAME}
    PRIVATE
        "${BOOST_JSON_SERIALIZER_TEST_SOURCE_DIR}"
        "${BOOST_JSON_SERIALIZER_INCLUDE_DIR}"
)

target_link_libraries(${BOOST_JSON_SERIALIZER_TEST_TARGET_NAME}
    PRIVATE
        framework::gtest_suite
        Boost::json
)

enable_testing()

gtest_discover_tests(${BOOST_JSON_SERIALIZER_TEST_TARGET_NAME})