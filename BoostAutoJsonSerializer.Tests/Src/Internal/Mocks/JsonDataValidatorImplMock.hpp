/*************************************************************************************************
 * @file JsonDataValidatorImplMock.hpp
 *
 * @brief Declarations for the concrete class which implements @ref IJsonDataValidatorImpl.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATAVALIDATORIMPLMOCK_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATAVALIDATORIMPLMOCK_HPP

#include "CommonTestsConfig.hpp"

#include "Interfaces/IJsonDataValidatorImpl.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Test
{
    /**
     * @class JsonDataValidatorImplMock
     *
     * @brief A mock class for the implementation class of @ref IJsonDataValidatorImpl.
     */
    class JsonDataValidatorImplMock : public Interfaces::IJsonDataValidatorImpl
    {
    public:
        MOCK_METHOD(void, Validate, (const std::string &payload), (override));

        // #endregion
    };
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATAVALIDATORIMPLMOCK_HPP