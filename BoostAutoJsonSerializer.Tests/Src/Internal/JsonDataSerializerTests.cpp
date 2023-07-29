/*************************************************************************************************
 * @file JsonDataSerializerTests.cpp
 *
 * @brief Contains unit tests for class @ref JsonDataSerializer.
 *
 *************************************************************************************************/

#include "CommonTestsConfig.hpp"

#include "Interfaces/Factories/IObjectFactories.hpp"
#include "Internal/JsonDataSerializer.hpp"

#include "Exceptions/XArgumentNull.hpp"
#include "Exceptions/XSerialization.hpp"

#include "Internal/Mocks/JsonDataSerializerImplMock.hpp"

// #region Namespace Symbols

using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Exceptions;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::FactoryInterfaces;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Interfaces;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Internal;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Test;

// #endregion

// #region GTest usings

using ::testing::_;
using ::testing::Eq;
using ::testing::Expectation;
using ::testing::NiceMock;
using ::testing::Ref;
using ::testing::Return;
using ::testing::Throw;

// #endregion

namespace
{
    /**
     * @class JsonDataSerializerTestsFactory
     *
     * @brief Class responsible to instantiate all the required classes.
     */
    class JsonDataSerializerTestsFactory
        : public IJsonDataSerializerFactory,
          public IJsonDataSerializerImplFactory
    {
    public:
        /**
         * @brief Create concrete instance of IJsonDataSerializer.
         *
         * @param[out] result An instance of class under test, @ref JsonDataSerializer.
         */
        void Create(IJsonDataSerializerFactory::InterfaceSharedPointer& objectPtr) override
        {
            IJsonDataSerializerImplFactory::InterfaceSharedPointer serializerImpl;
            Create(serializerImpl);

            objectPtr = std::make_shared<JsonDataSerializer>(serializerImpl);
        }

        void Create(IJsonDataSerializerImplFactory::InterfaceSharedPointer& objectPtr) override
        {
            objectPtr = (nullptr == _serializerImpl) ? std::make_shared<NiceMock<JsonDataSerializerImplMock>>() : _serializerImpl;
        }

        void Set(std::shared_ptr<IJsonDataSerializerImpl> serializerImpl)
        {
            _serializerImpl = serializerImpl;
        }

    private:
        std::shared_ptr<IJsonDataSerializerImpl> _serializerImpl;
    };

    /**
     * @class JsonDataSerializerTestFixture
     *
     * @brief Test fixture for JsonDataSerializer.
     *
     * This class provide access to the Factory and additional default to create fakes.
     */
    class JsonDataSerializerTestFixture : public ::testing::Test
    {
    public:
        /**
         * @brief Setup the factory. Method overriden from GTest framework class @ref ::testing::Test
         */
        void SetUp() override
        {
            _instanceFactory = std::make_shared<JsonDataSerializerTestsFactory>();
        }

        std::shared_ptr<JsonDataSerializerTestsFactory> GetFactory()
        {
            return _instanceFactory;
        }

        void Set(std::shared_ptr<JsonDataSerializerImplMock>& serializerImplMock)
        {
            _instanceFactory->Set(serializerImplMock);
        }

    private:
        std::shared_ptr<JsonDataSerializerTestsFactory> _instanceFactory;
    };

    // #region Unit Tests

    TEST_F(JsonDataSerializerTestFixture, SuccessfulInstanceCreation)
    {
        std::shared_ptr<IJsonDataSerializerFactory> jsonDataSerializerFactory = GetFactory();

        std::shared_ptr<IJsonDataSerializer> jsonDataSerializer;
        ASSERT_NO_THROW(jsonDataSerializerFactory->Create(jsonDataSerializer));
    }

    TEST_F(JsonDataSerializerTestFixture, ConstructorInvalidArgumentFailure)
    {
        // Arrange -> Act -> Assert
        ASSERT_THROW(JsonDataSerializer(nullptr), XArgumentNull);
    }

    TEST_F(JsonDataSerializerTestFixture, DeserializeSuccessful)
    {
        // Arrange
        std::string input = "This is input data";
        TestDataTestPolicy expectedTestPolicy = {};

        std::shared_ptr<JsonDataSerializerImplMock> serializerImplMock = std::make_shared<JsonDataSerializerImplMock>();
        Set(serializerImplMock);

        EXPECT_CALL(*serializerImplMock, Deserialize(Ref(input)))
            .Times(1)
            .WillOnce(Return(expectedTestPolicy));

        std::shared_ptr<IJsonDataSerializerFactory> jsonDataSerializerFactory = GetFactory();

        std::shared_ptr<IJsonDataSerializer> serializer;
        jsonDataSerializerFactory->Create(serializer);

        // Act
        TestDataTestPolicy actualTestPolicy = serializer->Deserialize(input);

        // Assert
        EXPECT_EQ(actualTestPolicy.Capabilities.size(), expectedTestPolicy.Capabilities.size());
        EXPECT_EQ(actualTestPolicy.Settings.size(), expectedTestPolicy.Settings.size());
    }

    TEST_F(JsonDataSerializerTestFixture, SerializeSuccessful)
    {
        // Arrange
        TestDataTestResults inputTestResults = {};

        std::string expectedOutput = "This is output data";

        std::shared_ptr<JsonDataSerializerImplMock> serializerImplMock = std::make_shared<JsonDataSerializerImplMock>();
        Set(serializerImplMock);

        EXPECT_CALL(*serializerImplMock, Serialize(Ref(inputTestResults)))
            .Times(1)
            .WillOnce(Return(expectedOutput));

        std::shared_ptr<IJsonDataSerializerFactory> jsonDataSerializerFactory = GetFactory();

        std::shared_ptr<IJsonDataSerializer> serializer;
        jsonDataSerializerFactory->Create(serializer);

        // Act
        std::string actualOutput = serializer->Serialize(inputTestResults);

        // Assert
        EXPECT_EQ(actualOutput, expectedOutput);
    }

    TEST_F(JsonDataSerializerTestFixture, ImplExceptionDeserializeFailure)
    {
        // Arrange
        std::string input = "This is input data";

        std::shared_ptr<JsonDataSerializerImplMock> serializerImplMock = std::make_shared<JsonDataSerializerImplMock>();
        Set(serializerImplMock);

        EXPECT_CALL(*serializerImplMock, Deserialize(Ref(input)))
            .Times(1)
            .WillOnce(Throw(XSerialization("Data de-serialization failed")));

        std::shared_ptr<IJsonDataSerializerFactory> jsonDataSerializerFactory = GetFactory();

        std::shared_ptr<IJsonDataSerializer> serializer;
        jsonDataSerializerFactory->Create(serializer);

        // Act -> Assert
        EXPECT_THROW(serializer->Deserialize(input), XSerialization);
    }

    TEST_F(JsonDataSerializerTestFixture, ImplExceptionSerializeFailure)
    {
        // Arrange
        TestDataTestResults inputTestResults = {};

        std::shared_ptr<JsonDataSerializerImplMock> serializerImplMock = std::make_shared<JsonDataSerializerImplMock>();
        Set(serializerImplMock);

        EXPECT_CALL(*serializerImplMock, Serialize(Ref(inputTestResults)))
            .Times(1)
            .WillOnce(Throw(XSerialization("Data serialization failed")));

        std::shared_ptr<IJsonDataSerializerFactory> jsonDataSerializerFactory = GetFactory();

        std::shared_ptr<IJsonDataSerializer> serializer;
        jsonDataSerializerFactory->Create(serializer);

        // Act -> Assert
        EXPECT_THROW(serializer->Serialize(inputTestResults), XSerialization);
    }

    // #endregion
} // Anonymous namespace