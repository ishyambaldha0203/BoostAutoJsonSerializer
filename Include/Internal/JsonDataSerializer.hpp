/*************************************************************************************************
 * @file JsonDataSerializer.hpp
 *
 * @brief Declarations for the concrete class @ref JsonDataSerializer.
 *
 * Serialization/de-serialization will happen to/from stringified JSON.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATASERIALIZER_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATASERIALIZER_HPP

#include "CommonConfig.hpp"

#include "Interfaces/IJsonDataSerializer.hpp"
#include "Interfaces/IJsonDataSerializerImpl.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    /**
     * @class JsonDataSerializer
     *
     * @brief Concrete implementation of JSON data serializer/de-serializer.
     */
    class JsonDataSerializer : public Interfaces::IJsonDataSerializer
    {
    public:
        // #region Construction/Destruction

        /**
         * @brief Construct a new test data serializer object.
         *
         * @param[in] impl Any instance of underlying implementation layer.
         *
         * @throw XArgumentNullException If input params are null.
         */
        explicit JsonDataSerializer(std::shared_ptr<Interfaces::IJsonDataSerializerImpl> impl);

        /**
         * @brief Destroy the JSON serializer object.
         */
        virtual ~JsonDataSerializer() override;

        // #endregion

        // #region IJsonDataSerializer Implementation

        virtual TestDataTestPolicy Deserialize(const std::string& payload) override;

        virtual std::string Serialize(const TestDataTestResults& entity) override;

        // #endregion

    private:
        DECLARE_NON_COPYABLE_CLASS(JsonDataSerializer)

        // #region Private Members

        /**
         * @brief An instance holding on to underlying serialization implementation.
         */
        std::shared_ptr<Interfaces::IJsonDataSerializerImpl> _impl;

        // #endregion
    };
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATASERIALIZER_HPP
