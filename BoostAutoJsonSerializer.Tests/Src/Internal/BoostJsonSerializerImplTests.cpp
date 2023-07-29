/*************************************************************************************************
 * @file BoostJsonSerializerImplTests.cpp
 *
 * @brief Contains unit tests for class @ref BoostJsonSerializerImpl.
 *
 *************************************************************************************************/

#include "CommonTestsConfig.hpp"

#include <cmath>

#include "Interfaces/Factories/IObjectFactories.hpp"
#include "Internal/BoostJsonSerializerImpl.hpp"
#include "Internal/BoostJsonSerializerInfra.hpp"

#include "Exceptions/XSerialization.hpp"

// #region Namespace Symbols

using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Exceptions;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::FactoryInterfaces;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Interfaces;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Internal;

namespace bj = boost::json;
namespace bv2 = boost::variant2;

// #endregion

namespace
{
    /**
     * @class BoostJsonSerializerImplTests
     *
     * @brief Class responsible to instantiate all the required classes.
     */
    class BoostJsonSerializerImplTests
        : public IJsonDataSerializerImplFactory
    {
    public:
        /**
         * @brief Create concrete instance of IJsonDataSerializerImpl.
         *
         * @param[out] result An instance of class under test, @ref BoostJsonSerializerImpl.
         */
        void Create(IJsonDataSerializerImplFactory::InterfaceSharedPointer &objectPtr) override
        {
            objectPtr = std::make_shared<BoostJsonSerializerImpl>();
        }
    };

    /**
     * @class BoostJsonSerializerImplTestFixture
     *
     * @brief Test fixture for BoostJsonSerializerImpl.
     *
     * This class provide access to the Factory and additional default to create fakes.
     */
    class BoostJsonSerializerImplTestFixture : public ::testing::Test
    {
    public:
        /**
         * @brief Setup the factory. Method overriden from GTest framework class @ref ::testing::Test
         */
        void SetUp() override
        {
            _instanceFactory = std::make_shared<BoostJsonSerializerImplTests>();
        }

        std::shared_ptr<BoostJsonSerializerImplTests> GetFactory()
        {
            return _instanceFactory;
        }

    private:
        std::shared_ptr<BoostJsonSerializerImplTests> _instanceFactory;
    };

    // #region Unit Tests

    // #region De-serialization Tests

    TEST_F(BoostJsonSerializerImplTestFixture, SuccessfulInstanceCreation)
    {
        std::shared_ptr<IJsonDataSerializerImplFactory> boostSerializerFactory = GetFactory();

        std::shared_ptr<IJsonDataSerializerImpl> boostSerializer;
        ASSERT_NO_THROW(boostSerializerFactory->Create(boostSerializer));
    }

    TEST_F(BoostJsonSerializerImplTestFixture, DeserializeSuccessful)
    {
        // Arrange
        std::string inputPayload = R"({
                                        "Capabilities": {
                                            "intKey": 123,
                                            "stringKey": "value",
                                            "boolKey": false,
                                            "doubleKey": 1.23,
                                            "negativeIntKey": -123,
                                            "negativeDoubleKey": -1.23
                                        },
                                        "Settings": {
                                            "intKey": 456,
                                            "stringKey": "value2",
                                            "boolKey": true,
                                            "doubleKey": 4.56,
                                            "negativeIntKey": -456,
                                            "negativeDoubleKey": -4.56
                                        }
                                    })";

        // Create boost serializer instance.
        std::shared_ptr<IJsonDataSerializerImplFactory> boostSerializerFactory = GetFactory();
        std::shared_ptr<IJsonDataSerializerImpl> boostSerializer;
        boostSerializerFactory->Create(boostSerializer);

        // Act
        TestDataTestPolicy testPolicy = boostSerializer->Deserialize(inputPayload);

        // Assert
        EXPECT_EQ(testPolicy.Capabilities.size(), 6);
        EXPECT_EQ(testPolicy.Settings.size(), 6);
        EXPECT_EQ(bv2::get<int64_t>(testPolicy.Capabilities["intKey"].data), 123);
        EXPECT_EQ(bv2::get<std::string>(testPolicy.Capabilities["stringKey"].data), "value");
        EXPECT_EQ(bv2::get<bool>(testPolicy.Capabilities["boolKey"].data), false);
        ASSERT_DOUBLE_EQ(bv2::get<double>(testPolicy.Capabilities["doubleKey"].data), 1.23);
        EXPECT_EQ(bv2::get<int64_t>(testPolicy.Capabilities["negativeIntKey"].data), -123);
        ASSERT_DOUBLE_EQ(bv2::get<double>(testPolicy.Capabilities["negativeDoubleKey"].data), -1.23);

        EXPECT_EQ(bv2::get<int64_t>(testPolicy.Settings["intKey"].data), 456);
        EXPECT_EQ(bv2::get<std::string>(testPolicy.Settings["stringKey"].data), "value2");
        EXPECT_EQ(bv2::get<bool>(testPolicy.Settings["boolKey"].data), true);
        ASSERT_DOUBLE_EQ(bv2::get<double>(testPolicy.Settings["doubleKey"].data), 4.56);
        EXPECT_EQ(bv2::get<int64_t>(testPolicy.Settings["negativeIntKey"].data), -456);
        ASSERT_DOUBLE_EQ(bv2::get<double>(testPolicy.Settings["negativeDoubleKey"].data), -4.56);
    }

    /**
     * @brief Invalid payload data sets.
     */
    struct InputPayloadJsonData
    {
        std::string payload;
        const char *testCaseName;
    };

    class BoostJsonSerializerImplTestFixtureWithParams
        : public BoostJsonSerializerImplTestFixture,
          public ::testing::WithParamInterface<InputPayloadJsonData>
    {
    };

    /**
     * @brief Test case parameters for TestDataTestPolicy::Capabilities.
     */
    const std::array<InputPayloadJsonData, 8> InvalidPayloadArray =
        {
            InputPayloadJsonData{
                "",
                "EmptyPayloadFailure"},
            InputPayloadJsonData{
                R"({"Capabilities": {"key" -> "value"}})",
                "InvalidJsonFailure"},
            InputPayloadJsonData{
                R"({"Capabilities": {"intKey": 123}})",
                "MissingCapabilitiesFailure"},
            InputPayloadJsonData{
                R"({"Settings": {"stringKey": "value2"}})",
                "MissingSettingsFailure"},
            InputPayloadJsonData{
                R"({"Capabilities": {"arrayKey": [1, 2, 3]}})",
                "CapabilitiesWithArrayFailure"},
            InputPayloadJsonData{
                R"({"Settings": {"arrayKey": [1, 2, 3]}})",
                "SettingsWithArrayFailure"},
            InputPayloadJsonData{
                R"({"Capabilities": {"objectKey": {"key": "value"}}})",
                "CapabilitiesWithObjectFailure"},
            InputPayloadJsonData{
                R"({"Settings": {"objectKey": {"key": "value"}}})",
                "SettingsWithObjectFailure"}};

    TEST_P(BoostJsonSerializerImplTestFixtureWithParams, DeserializeFailure)
    {
        // Arrange
        std::shared_ptr<IJsonDataSerializerImplFactory> boostSerializerFactory = GetFactory();
        std::shared_ptr<IJsonDataSerializerImpl> boostSerializer;
        boostSerializerFactory->Create(boostSerializer);

        // Act -> Assert
        EXPECT_THROW(boostSerializer->Deserialize(GetParam().payload), XSerialization);
    }

    INSTANTIATE_TEST_CASE_P(
        BoostJsonSerializerImplTestWithParams,
        BoostJsonSerializerImplTestFixtureWithParams,
        testing::ValuesIn(InvalidPayloadArray),
        [](const ::testing::TestParamInfo<InputPayloadJsonData> &info)
        {
            return info.param.testCaseName;
        });

    // #endregion

    // #region Serialization Tests

    // #region Custom JSON Comparator Methods

    /**
     * @brief Supporting function to below 'AreEqual' method.
     *
     * @param lhs A floating type value.
     * @param rhs Another floating type value. for comparison.
     * @return bool @b true if equal, @b false otherwise.
     */
    bool AreEqual(float lhs, float rhs, float epsilon = 0.001f)
    {
        return std::fabs(lhs - rhs) < epsilon;
    }

    /**
     * @brief Supporting function to below 'AreEqual' method.
     *
     * @param lhs A boost::json::value object.
     * @param rhs Another boost::json::value object for comparison.
     * @return bool @b true if equal, @b false otherwise.
     */
    bool AreEqual(const boost::json::value &lhs, const boost::json::value &rhs)
    {
        // Compare the JSON values.
        if (lhs.kind() != rhs.kind())
            return false;

        if (lhs.is_double() && rhs.is_double())
            return AreEqual(lhs.as_double(), rhs.as_double());

        if (lhs.is_array() && rhs.is_array())
        {
            const boost::json::array &lhsArray = lhs.as_array();
            const boost::json::array &rhsArray = rhs.as_array();

            if (lhsArray.size() != rhsArray.size())
                return false;

            for (size_t i = 0; i < lhsArray.size(); ++i)
                if (!AreEqual(lhsArray[i], rhsArray[i]))
                    return false;

            return true;
        }

        if (lhs.is_object() && rhs.is_object())
        {
            const boost::json::object &lhsObject = lhs.as_object();
            const boost::json::object &rhsObject = rhs.as_object();

            if (lhsObject.size() != rhsObject.size())
                return false;

            for (boost::json::object::const_iterator it = lhsObject.begin(); it != lhsObject.end(); ++it)
                if (!AreEqual(it->value(), rhsObject.at(it->key())))
                    return false;

            return true;
        }

        return lhs == rhs;
    }

    /**
     * @brief Using custom parser to compare the JSON key by key.
     *
     * @param lhs JSON payload.
     * @param rhs Another JSON payload for comparison.
     * @return bool @b true if equal, @b false otherwise.
     */
    bool AreEqual(const std::string &lhs, const std::string &rhs)
    {
        // Parse the strings as JSON values.
        boost::json::value aValue = boost::json::parse(lhs);
        boost::json::value bValue = boost::json::parse(rhs);

        // Compare the JSON values.
        return AreEqual(aValue, bValue);
    }

    // #endregion

    /**
     * @brief Create an instance of TestDataTestResults with some sample data.
     *
     * @return TestDataTestResults A structure filled with data.
     */
    TestDataTestResults CreateTestDataTestResultsInstance()
    {
        // Create an instance of TestDataTestResults with some sample data
        TestDataTestResults testResults;

        // Add a MonitorResult.
        TestDataMonitorResults monitorResult;
        testResults.MonitorResults.push_back(monitorResult);

        // Add a StepResult to the MonitorResult.
        TestDataStepResults stepResult;
        testResults.MonitorResults.back().StepResults.push_back(stepResult);

        // Add a Metric to the StepResult.
        TestDataMetrics metric;
        testResults.MonitorResults.back().StepResults.back().Metrics.push_back(metric);

        // Add some MetricData to the Metric.
        testResults.MonitorResults.back().StepResults.back().Metrics.back().MetricData["string_key"] = {std::string("string_value")};
        testResults.MonitorResults.back().StepResults.back().Metrics.back().MetricData["float_key"] = {123.45f};
        testResults.MonitorResults.back().StepResults.back().Metrics.back().MetricData["int_key"] = {123};
        testResults.MonitorResults.back().StepResults.back().Metrics.back().MetricData["bool_key"] = {true};
        testResults.MonitorResults.back().StepResults.back().Metrics.back().MetricData["negative_int_key"] = {-123};

        // Add some OtherData to the StepResult.
        testResults.MonitorResults.back().StepResults.back().OtherData["other_string_key"] = {std::string("other_string_value")};

        return testResults;
    }

    TEST_F(BoostJsonSerializerImplTestFixture, SerializeSuccessful)
    {
        // Arrange
        std::string expectedResult = R"({
                                        "MonitorResults": [
                                            {
                                                "StepResults": [
                                                    {
                                                        "Metrics": [
                                                            {
                                                                "MetricData": {
                                                                    "bool_key": true,
                                                                    "float_key": 123.45,
                                                                    "int_key": 123,
                                                                    "negative_int_key": -123,
                                                                    "string_key": "string_value"
                                                                }
                                                            }
                                                        ],
                                                        "OtherData": {
                                                            "other_string_key": "other_string_value"
                                                        },
                                                        "PageResults": {}
                                                    }
                                                ],
                                                "OtherData": {}
                                            }
                                        ],
                                        "OtherData": {}
                                    })";

        TestDataTestResults inputTestResults = CreateTestDataTestResultsInstance();

        // Create boost serializer instance.
        std::shared_ptr<IJsonDataSerializerImplFactory> boostSerializerFactory = GetFactory();
        std::shared_ptr<IJsonDataSerializerImpl> boostSerializer;
        boostSerializerFactory->Create(boostSerializer);

        // Act
        std::string actualResult = boostSerializer->Serialize(inputTestResults);

        // Assert
        EXPECT_TRUE(AreEqual(expectedResult, actualResult));
    }

    // #endregion
} // Anonymous namespace