/*************************************************************************************************
 * @file BoostJsonSerializerImpl.cpp
 *
 * @brief Concrete implementation of @ref BoostJsonSerializerImpl class.
 *
 * To manage underlying implementation layer of @ref JsonDataSerializer.
 *
 *************************************************************************************************/

#include "Internal/BoostJsonSerializerImpl.hpp"
#include "Internal/BoostJsonSerializerInfra.hpp"

#include "Exceptions/XSerialization.hpp"
#include "Exceptions/XArgumentNull.hpp"

// #region Namespace Symbols

using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Exceptions;

// #endregion

namespace
{
    /**
     * @brief A common exception handler that handles all exceptions related to serialization errors.
     *
     * @param[in] ex base exception which is carrying actual exception object.
     * @param[in] errorMessage A message to prefixed with exception info.
     */
    [[noreturn]] void ThrowSerializationException(const std::exception& ex,
                                                  const std::string& errorMessage)
    {
        const std::set<const std::type_info*> SerializationException = {
            /* &typeid(boost::wrapexcept<std::bad_alloc>) */
            &typeid(boost::wrapexcept<std::invalid_argument>),
            &typeid(boost::wrapexcept<std::length_error>),
            &typeid(boost::wrapexcept<std::out_of_range>),
            &typeid(boost::wrapexcept<boost::system::system_error>)};

        if (SerializationException.count(&typeid(ex)))
        {
            throw XSerialization(errorMessage + std::string(" -> ") + ex.what());
        }

        throw;
    }
}

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    namespace bj = boost::json;

    // #region Construction/Destruction

    BoostJsonSerializerImpl::BoostJsonSerializerImpl() = default;

    BoostJsonSerializerImpl::~BoostJsonSerializerImpl() = default;

    // #endregion

    // #region Public Methods

    TestDataTestPolicy BoostJsonSerializerImpl::Deserialize(const std::string& payload)
    {
        try
        {
            // Parse the stringified JSON to object.
            bj::value bjValue = bj::parse(payload);

            // Deserialize to data structure.
            TestDataTestPolicy testPolicy = bj::value_to<TestDataTestPolicy>(bjValue);

            return testPolicy;
        }
        catch (const std::exception& ex)
        {
            ThrowSerializationException(ex, "Deserialization");
        }
    }

    std::string BoostJsonSerializerImpl::Serialize(const TestDataTestResults& entity)
    {
        try
        {
            bj::value bjValue = bj::value_from(entity);

            std::string resultPayload = bj::serialize(bjValue);

            return resultPayload;
        }
        catch (const std::exception& ex)
        {
            ThrowSerializationException(ex, "Serialization");
        }
    }

    // #endregion

} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS