#
# This is a CMake project file for Boost Auto JSON Serializer library.
#
cmake_minimum_required(VERSION 3.19.0)

project(BoostAutoJsonSerializer VERSION 0.0.0.1 LANGUAGES CXX)

################################################################
# Configurations
################################################################
include(${CMAKE_CURRENT_SOURCE_DIR}/Build/DefaultCmakeSettings.cmake)

set(CMAKE_BUILD_TYPE Debug)

################################################################
# VARIABLES
################################################################
set(BOOST_JSON_SERIALIZER_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")
set(BOOST_JSON_SERIALIZER_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Src")
set(BOOST_JSON_SERIALIZER_TARGET_NAME boost_json_serializer)

################################################################
# DEPENDENCIES
################################################################
find_package(Boost REQUIRED COMPONENTS json)

################################################################
# TARGESTS
################################################################

# Add source to this project's executable.
add_executable(${BOOST_JSON_SERIALIZER_TARGET_NAME})
add_subdirectory(${BOOST_JSON_SERIALIZER_SOURCE_DIR})

################################################################
# INCLUDES
################################################################

target_include_directories(${BOOST_JSON_SERIALIZER_TARGET_NAME} PRIVATE
    ${BOOST_JSON_SERIALIZER_INCLUDE_DIR}
)

target_link_libraries(${BOOST_JSON_SERIALIZER_TARGET_NAME} PRIVATE
    Boost::json
)
