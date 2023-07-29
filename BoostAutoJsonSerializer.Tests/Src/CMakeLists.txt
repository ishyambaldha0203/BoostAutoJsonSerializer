################################################################
# SOURCE
################################################################
### NOTE: This file should list all source files regardless of where in the directory tree they reside.
### The main CMake file does not know nor care where the sources are.
target_sources(${BOOST_JSON_SERIALIZER_TEST_TARGET_NAME}
    PRIVATE
        # Src/Internal
        "${CMAKE_CURRENT_LIST_DIR}/Internal/BoostJsonSerializerImplTests.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../../Src/Internal/BoostJsonSerializerImpl.cpp"

        "${CMAKE_CURRENT_LIST_DIR}/Internal/BoostJsonValidatorImplTests.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../../Src/Internal/BoostJsonValidatorImpl.cpp"

        "${CMAKE_CURRENT_LIST_DIR}/Internal/JsonDataSerializerTests.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../../Src/Internal/JsonDataSerializer.cpp"

        "${CMAKE_CURRENT_LIST_DIR}/Internal/JsonDataValidatorTests.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/../../Src/Internal/JsonDataValidator.cpp"
)