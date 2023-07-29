/*************************************************************************************************
 * @file JsonDataValidatorTests.cpp
 *
 * @brief Contains unit tests for class @ref JsonDataValidator.
 *
 *************************************************************************************************/

#include "CommonTestsConfig.hpp"

#include "Interfaces/Factories/IObjectFactories.hpp"
#include "Internal/JsonDataValidator.hpp"

#include "Exceptions/XArgumentNull.hpp"
#include "Exceptions/XInvalidFormat.hpp"

#include "Internal/Mocks/JsonDataValidatorImplMock.hpp"

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
using ::testing::Throw;

// #endregion

namespace
{
    /**
     * @class JsonDataValidatorTestsFactory
     *
     * @brief Class responsible to instantiate all the required classes.
     */
    class JsonDataValidatorTestsFactory
        : public IJsonDataValidatorFactory,
          public IJsonDataValidatorImplFactory
    {
    public:
        /**
         * @brief Create concrete instance of IJsonDataValidator.
         *
         * @param[out] result An instance of class under test, @ref JsonDataValidator.
         */
        void Create(IJsonDataValidatorFactory::InterfaceSharedPointer& objectPtr) override
        {
            IJsonDataValidatorImplFactory::InterfaceSharedPointer validatorImpl;
            Create(validatorImpl);

            objectPtr = std::make_shared<JsonDataValidator>(validatorImpl);
        }

        void Create(IJsonDataValidatorImplFactory::InterfaceSharedPointer& objectPtr) override
        {
            objectPtr = (nullptr == _validatorImpl) ? std::make_shared<NiceMock<JsonDataValidatorImplMock>>() : _validatorImpl;
        }

        void Set(std::shared_ptr<IJsonDataValidatorImpl> validatorImpl)
        {
            _validatorImpl = validatorImpl;
        }

    private:
        std::shared_ptr<IJsonDataValidatorImpl> _validatorImpl;
    };

    /**
     * @class JsonDataValidatorTestFixture
     *
     * @brief Test fixture for JsonDataValidator.
     *
     * This class provide access to the Factory and additional default to create fakes.
     */
    class JsonDataValidatorTestFixture : public ::testing::Test
    {
    public:
        /**
         * @brief Setup the factory. Method overriden from GTest framework class @ref ::testing::Test
         */
        void SetUp() override
        {
            _instanceFactory = std::make_shared<JsonDataValidatorTestsFactory>();
        }

        std::shared_ptr<JsonDataValidatorTestsFactory> GetFactory()
        {
            return _instanceFactory;
        }

        void Set(std::shared_ptr<JsonDataValidatorImplMock>& validatorImplMock)
        {
            _instanceFactory->Set(validatorImplMock);
        }

    private:
        std::shared_ptr<JsonDataValidatorTestsFactory> _instanceFactory;
    };

    // #region Unit Tests

    TEST_F(JsonDataValidatorTestFixture, SuccessfulInstanceCreation)
    {
        std::shared_ptr<IJsonDataValidatorFactory> jsonDataValidatorFactory = GetFactory();

        std::shared_ptr<IJsonDataValidator> jsonDataValidator;
        ASSERT_NO_THROW(jsonDataValidatorFactory->Create(jsonDataValidator));
    }

    TEST_F(JsonDataValidatorTestFixture, ConstructorInvalidArgumentFailure)
    {
        // Arrange -> Act -> Assert
        ASSERT_THROW(JsonDataValidator(nullptr), XArgumentNull);
    }

    TEST_F(JsonDataValidatorTestFixture, ValidateSuccessful)
    {
        // Arrange
        std::string input = "This is input to validate";

        std::shared_ptr<JsonDataValidatorImplMock> validatorImplMock = std::make_shared<JsonDataValidatorImplMock>();
        Set(validatorImplMock);

        EXPECT_CALL(*validatorImplMock, Validate(input))
            .Times(1);

        std::shared_ptr<IJsonDataValidatorFactory> jsonDataValidatorFactory = GetFactory();

        std::shared_ptr<IJsonDataValidator> validator;
        jsonDataValidatorFactory->Create(validator);

        // Act -> Assert
        EXPECT_NO_THROW(validator->Validate(input));
    }

    TEST_F(JsonDataValidatorTestFixture, ImplValidatorExceptionValidateFailure)
    {
        // Arrange
        std::string input = "This is input to validate";

        std::shared_ptr<JsonDataValidatorImplMock> validatorImplMock = std::make_shared<JsonDataValidatorImplMock>();
        Set(validatorImplMock);

        EXPECT_CALL(*validatorImplMock, Validate(input))
            .Times(1)
            .WillOnce(Throw(XInvalidFormat("Invalid data format")));

        std::shared_ptr<IJsonDataValidatorFactory> jsonDataValidatorFactory = GetFactory();

        std::shared_ptr<IJsonDataValidator> validator;
        jsonDataValidatorFactory->Create(validator);

        // Act -> Assert
        EXPECT_THROW(validator->Validate(input), XInvalidFormat);
    }

    // #endregion
} // Anonymous namespace