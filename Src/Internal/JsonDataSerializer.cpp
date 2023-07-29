/*************************************************************************************************
 * @file JsonDataSerializer.cpp
 *
 * @brief Concrete implementation of @ref JsonDataSerializer class.
 *
 * To manage serialization and de-serialization of input and output to/from JSONised string formatted data.
 *
 *************************************************************************************************/

#include "Internal/JsonDataSerializer.hpp"

#include "Exceptions/XArgumentNull.hpp"

// #region Namespace Symbols

using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Exceptions;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Interfaces;

// #endregion

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    // #region Construction/Destruction

    JsonDataSerializer::JsonDataSerializer(std::shared_ptr<IJsonDataSerializerImpl> impl)
        : _impl(impl)
    {
        if (nullptr == _impl)
        {
            throw XArgumentNull("JsonDataSerializer::impl");
        }
    }

    JsonDataSerializer::~JsonDataSerializer() = default;

    // #endregion

    // #region Public Methods

    TestDataTestPolicy JsonDataSerializer::Deserialize(const std::string& payload)
    {
        return _impl->Deserialize(payload);
    }

    std::string JsonDataSerializer::Serialize(const TestDataTestResults& entity)
    {
        return _impl->Serialize(entity);
    }

    // #endregion

} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS