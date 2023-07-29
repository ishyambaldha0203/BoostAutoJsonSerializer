/**********************************************************************
 * @file JsonDataSerializerMock.hpp
 *
 * @brief Declaration of mocked methods for class @ref estDataSerializer.
 *
 * It is required only for unit testing.
 *
 *********************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_TESTS_INTERNAL_MOCKS_JSONDATASERIALIZERMOCK_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_TESTS_INTERNAL_MOCKS_JSONDATASERIALIZERMOCK_HPP

#include "CommonTestsConfig.hpp"

#include "Interfaces/IJsonDataSerializer.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Test
{
    /**u
     * @class JsonDataSerializerMock
     *
     * @brief A mock class for @ref JsonDataSerializer.
     */
    class JsonDataSerializerMock : public Interfaces::IJsonDataSerializer
    {
    public:
        MOCK_METHOD(Internal::TestDataTestPolicy, Deserialize, (const std::string &payload), (override));
        MOCK_METHOD(std::string, Serialize, (const Internal::TestDataTestResults &entity), (override));
    };
}
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_TESTS_INTERNAL_MOCKS_JSONDATASERIALIZERMOCK_HPP
