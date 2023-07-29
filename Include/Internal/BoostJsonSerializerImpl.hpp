/*************************************************************************************************
 * @file BoostJsonSerializerImpl.hpp
 *
 * @brief Declarations for the concrete class @ref BoostJsonSerializerImpl.
 *
 * It contains declarations of underlying implementation layer of @ref JsonDataSerializer.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_BOOSTJSONSERIALIZERIMPL_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_BOOSTJSONSERIALIZERIMPL_HPP

#include "CommonConfig.hpp"

#include "Interfaces/IJsonDataSerializerImpl.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    /**
     * @class BoostJsonSerializerImpl
     *
     * @brief Concrete implementation of underlying impl layer of test data serialization.
     */
    class BoostJsonSerializerImpl : public Interfaces::IJsonDataSerializerImpl
    {
    public:
        // #region Construction/Destruction

        /**
         * @brief Construct a new implementation layer object of boost json serializer.
         */
        BoostJsonSerializerImpl();

        /**
         * @brief Destroy implementation layer object of boost json serializer.
         */
        virtual ~BoostJsonSerializerImpl() override;

        // #endregion

        // #region IJsonDataSerializerImpl Implementation

        virtual TestDataTestPolicy Deserialize(const std::string& payload) override;

        virtual std::string Serialize(const TestDataTestResults& entity) override;

        // #endregion

    private:
        DECLARE_NON_COPYABLE_CLASS(BoostJsonSerializerImpl)
    };
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERNAL_BOOSTJSONSERIALIZERIMPL_HPP
