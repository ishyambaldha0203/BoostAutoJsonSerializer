/*************************************************************************************************
 * @file BoostJsonValidatorImpl.cpp
 *
 * @brief Concrete implementation of @ref BoostJsonValidatorImpl class.
 *
 * To manage underlying implementation layer of @ref JsonDataValidator.
 *
 *************************************************************************************************/

#include "Internal/BoostJsonValidatorImpl.hpp"
#include "Exceptions/XInvalidFormat.hpp"

// #region Namespace Symbols

using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Exceptions;

// #endregion

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    namespace bj = boost::json;

    // #region Construction/Destruction

    BoostJsonValidatorImpl::BoostJsonValidatorImpl() = default;

    BoostJsonValidatorImpl::~BoostJsonValidatorImpl() = default;

    // #endregion

    // #region Public Methods

    void BoostJsonValidatorImpl::Validate(const std::string& payload)
    {
        bj::error_code errorCode;

        // It will set the error code if there is any glitch with the provided json payload.
        bj::parse(payload, errorCode);

        if (errorCode)
        {
            throw XInvalidFormat(std::string("Invalid JSON payload: ") + errorCode.message());
        }
    }

    // #endregion

} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS