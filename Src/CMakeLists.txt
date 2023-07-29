################################################################
# SOURCE
################################################################
### NOTE: This file should list all source files regardless of where in the directory tree they reside.
### The main CMake file does not know nor care where the sources are.
target_sources(${BOOST_JSON_SERIALIZER_TARGET_NAME}
    PRIVATE
        # Src
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp

        # Src/Internal
        ${CMAKE_CURRENT_LIST_DIR}/Internal/BoostJsonSerializerImpl.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Internal/BoostJsonValidatorImpl.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Internal/ObjectFactory.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Internal/Program.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Internal/JsonDataSerializer.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Internal/JsonDataValidator.cpp
)
