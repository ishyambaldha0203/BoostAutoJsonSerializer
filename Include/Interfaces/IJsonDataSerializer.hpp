/*************************************************************************************************
 * @file IJsonDataSerializer.hpp
 *
 * @brief Interface to define member contracts to serialize/de-serialize the data.
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATASERIALIZER_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATASERIALIZER_HPP

#include "CommonConfig.hpp"

#include "Internal/SerializableDataModels.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Interfaces
{
    /**
     * @interface IJsonDataSerializer
     *
     * @brief Interface to define member contracts and operations to serialize/de-serialize .
     */
    interface IJsonDataSerializer
    {
        DECLARE_INTERFACE_DEFAULTS(IJsonDataSerializer)

        /**
         * @brief Deserialize the stringified JSON that provided as input.
         *
         * @param[in] payload String formatted json payload.
         *
         * @return A data entity.
         *
         * @throw XSerialization If deserialization failed due to any reason.
         */
        virtual Internal::TestDataTestPolicy Deserialize(const std::string& payload) = 0;

        /**
         * @brief Serialize the provided input structures to stringified json.
         *
         * @param[in] entity Test result data entity.
         *
         * @return Test result in string formatted formatted json.
         *
         * @throw XSerialization If serialization failed due to any reason.
         */
        virtual std::string Serialize(const Internal::TestDataTestResults& entity) = 0;
    };
} // namespace Interfaces
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATASERIALIZER_HPP