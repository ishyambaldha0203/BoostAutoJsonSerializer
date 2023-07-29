/*************************************************************************************************
 * @file JsonDataValidator.cpp
 *
 * @brief Concrete implementation of @ref JsonDataValidator class.
 *
 * To validate the stringified JSON provided as input.
 *
 *************************************************************************************************/

#include "Internal/JsonDataValidator.hpp"

#include "Exceptions/XArgumentNull.hpp"

// #region Namespace Symbols

using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Exceptions;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Interfaces;

// #endregion

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    // #region Construction/Destruction

    JsonDataValidator::JsonDataValidator(std::shared_ptr<IJsonDataValidatorImpl> impl)
        : _impl(impl)
    {
        if (nullptr == _impl)
        {
            throw XArgumentNull("JsonDataValidator::impl");
        }
    }

    JsonDataValidator::~JsonDataValidator() = default;

    // #endregion

    // #region Public Methods

    void JsonDataValidator::Validate(const std::string& payload)
    {
        _impl->Validate(payload);
    }

    // #endregion

} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS