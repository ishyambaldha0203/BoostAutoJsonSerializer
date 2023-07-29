/*************************************************************************************************
 * @file BoostJsonValidatorImplTests.cpp
 *
 * @brief Contains unit tests for class @ref BoostJsonValidatorImpl.
 *
 *************************************************************************************************/

#include "CommonTestsConfig.hpp"

#include "Interfaces/Factories/IObjectFactories.hpp"
#include "Internal/BoostJsonValidatorImpl.hpp"

#include "Exceptions/XInvalidFormat.hpp"

// #region Namespace Symbols

using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Exceptions;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::FactoryInterfaces;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Interfaces;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Internal;

namespace bj = boost::json;

// #endregion

namespace
{
    /**
     * @class BoostJsonValidatorImplTests
     *
     * @brief Class responsible to instantiate all the required classes.
     */
    class BoostJsonValidatorImplTests
        : public IJsonDataValidatorImplFactory
    {
    public:
        /**
         * @brief Create concrete instance of IJsonDataValidatorImpl.
         *
         * @param[out] result An instance of class under test, @ref BoostJsonValidatorImpl.
         */
        void Create(IJsonDataValidatorImplFactory::InterfaceSharedPointer& objectPtr) override
        {
            objectPtr = std::make_shared<BoostJsonValidatorImpl>();
        }
    };

    /**
     * @class BoostJsonValidatorImplTestFixture
     *
     * @brief Test fixture for BoostJsonValidatorImpl.
     *
     * This class provide access to the Factory and additional default to create fakes.
     */
    class BoostJsonValidatorImplTestFixture : public ::testing::Test
    {
    public:
        /**
         * @brief Setup the factory. Method overriden from GTest framework class @ref ::testing::Test
         */
        void SetUp() override
        {
            _instanceFactory = std::make_shared<BoostJsonValidatorImplTests>();
        }

        std::shared_ptr<BoostJsonValidatorImplTests> GetFactory()
        {
            return _instanceFactory;
        }

    private:
        std::shared_ptr<BoostJsonValidatorImplTests> _instanceFactory;
    };

    // #region Unit Tests

    TEST_F(BoostJsonValidatorImplTestFixture, SuccessfulInstanceCreation)
    {
        std::shared_ptr<IJsonDataValidatorImplFactory> boostValidatorFactory = GetFactory();

        std::shared_ptr<IJsonDataValidatorImpl> boostValidator;
        ASSERT_NO_THROW(boostValidatorFactory->Create(boostValidator));
    }

    TEST_F(BoostJsonValidatorImplTestFixture, ValidateSuccessful)
    {
        // Arrange
        std::string inputPayload = R"({
                                        "Object1": {
                                            "intKey": 123,
                                            "stringKey": "value",
                                            "boolKey": false,
                                            "doubleKey": 1.23,
                                            "negativeIntKey": -123,
                                            "negativeDoubleKey": -1.23
                                        },
                                        "Object2": {
                                            "intKey": 456,
                                            "stringKey": "value2",
                                            "boolKey": true,
                                            "doubleKey": 4.56,
                                            "negativeIntKey": -456,
                                            "negativeDoubleKey": -4.56
                                        }
                                    })";

        // Create boost validator instance.
        std::shared_ptr<IJsonDataValidatorImplFactory> boostValidatorFactory = GetFactory();
        std::shared_ptr<IJsonDataValidatorImpl> boostValidator;
        boostValidatorFactory->Create(boostValidator);

        // Act -> Assert
        EXPECT_NO_THROW(boostValidator->Validate(inputPayload));
    }

    /**
     * @brief Invalid payload data sets.
     */
    struct InputPayloadJsonData
    {
        std::string payload;
        const char* testCaseName;
    };

    class BoostJsonValidatorImplTestFixtureWithParams
        : public BoostJsonValidatorImplTestFixture,
          public ::testing::WithParamInterface<InputPayloadJsonData>
    {
    };

    /**
     * @brief Test case parameters for TestDataTestPolicy::Capabilities.
     */
    const std::array<InputPayloadJsonData, 3> InvalidPayloadArray =
        {
            InputPayloadJsonData{
                "",
                "EmptyPayloadFailure"},
            InputPayloadJsonData{
                R"({"object": {"key" -> "value"}})",
                "InvalidJsonFailure"},
            InputPayloadJsonData{
                "{\"object\": {\"key\": \"@#%^&*(){}[]|;:'\"<>,./?\"}}",
                "SpecialCharactersFailure"}
        };

    TEST_P(BoostJsonValidatorImplTestFixtureWithParams, ValidateFailure)
    {
        // Arrange
        std::shared_ptr<IJsonDataValidatorImplFactory> boostValidatorFactory = GetFactory();
        std::shared_ptr<IJsonDataValidatorImpl> boostValidator;
        boostValidatorFactory->Create(boostValidator);

        // Act -> Assert
        EXPECT_THROW(boostValidator->Validate(GetParam().payload), XInvalidFormat);
    }

    INSTANTIATE_TEST_CASE_P(
        BoostJsonValidatorImplTestWithParams,
        BoostJsonValidatorImplTestFixtureWithParams,
        testing::ValuesIn(InvalidPayloadArray),
        [](const ::testing::TestParamInfo<InputPayloadJsonData>& info)
        {
            return info.param.testCaseName;
        });

    // #endregion
} // Anonymous namespace