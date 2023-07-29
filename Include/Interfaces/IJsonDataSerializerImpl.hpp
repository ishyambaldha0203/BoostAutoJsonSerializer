/*************************************************************************************************
 * @file IJsonDataSerializerImpl.hpp
 *
 * @brief Contains the interface to define member contracts of implementation layer of @ref IJsonDataSerializer.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATASERIALIZERIMPL_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATASERIALIZERIMPL_HPP

#include "CommonConfig.hpp"

#include "Internal/SerializableDataModels.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Interfaces
{
    /**
     * @interface IJsonDataSerializerImpl
     *
     * @brief Interface to define member contracts and operations implementation layer of @ref IJsonDataSerializer.
     */
    interface IJsonDataSerializerImpl
    {
        DECLARE_INTERFACE_DEFAULTS(IJsonDataSerializerImpl)

        /**
         * @brief Deserialize the stringified JSON data provided as input.
         *
         * @param[in] payload String formatted json payload.
         *
         * @return A data entity.
         *
         * @throw XSerialization If deserialization failed due to any reason.
         */
        virtual Internal::TestDataTestPolicy Deserialize(const std::string& payload) = 0;

        /**
         * @brief Serialize the provided data filled structure to stringified json.
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

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATASERIALIZERIMPL_HPP