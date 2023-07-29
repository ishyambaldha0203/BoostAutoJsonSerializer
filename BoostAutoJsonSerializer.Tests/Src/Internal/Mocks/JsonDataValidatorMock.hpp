/*************************************************************************************************
 * @file JsonDataValidatorMock.hpp
 *
 * @brief Declarations for the concrete class @ref JsonDataValidator.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATAVALIDATORMOCK_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATAVALIDATORMOCK_HPP

#include "CommonTestsConfig.hpp"

#include "Interfaces/IJsonDataValidator.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Test
{
    /**
     * @class JsonDataValidatorMock
     *
     * @brief A mock class for @ref JsonDataValidator.
     */
    class JsonDataValidatorMock : public Interfaces::IJsonDataValidator
    {
    public:
        MOCK_METHOD(void, Validate, (const std::string &payload), (override));

        // #endregion
    };
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATAVALIDATORMOCK_HPP
