/*************************************************************************************************
 * @file SerializableDataModels.hpp
 *
 * @brief Constains data structures used for de/serialization of json data
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_SERIALIZABLEDATAMODELS_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_SERIALIZABLEDATAMODELS_HPP

#include "CommonConfig.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    // #region Generic Datatype

    /**
     * @brief Variant type to hold the test policy data values of all possible data type.
     */
    using DeserializationVariant = boost::variant2::variant<std::string, int64_t, uint64_t, double, bool>;

    /**
     * @brief A simple container for holding test policy boost::variant type
     *
     * @note If using boost.json for serialization,
     * + This container is necessary to wrap boost::variant in such a way that the boost::json::tag_invoke
     * functions are actually able to be auto deduced the type properly.
     * + Overloaded boost::json::tag_invoke method is not working with variant and throwing compilation error.
     */
    struct DeserializationValue
    {
        DeserializationVariant data;
    };

    /**
     * @brief Variant type to hold the test result data values of all possible data type.
     */
    using SerializationVariant =
        boost::variant2::variant<std::string, bool, float, int8_t, int16_t, int32_t, int64_t, uint8_t, uint16_t, uint32_t, uint64_t>;

    /**
     * @brief A simple container for holding test result boost::variant type.
     *
     * @note If using boost.json for serialization,
     * + This container is necessary to wrap boost::variant in such a way that the boost::json::tag_invoke
     * functions are actually able to be auto deduced the type properly.
     * + Overloaded boost::json::tag_invoke method is not working with variant and throwing compilation error.
     */
    struct SerializationValue
    {
        SerializationVariant data;
    };

    // #endregion

    // #region TestConfiguration Data Objects

    /**
     * @struct TestDataTestPolicy
     *
     * @brief The input configuration required by the monitor.
     */
    struct TestDataTestPolicy
    {
        std::map<std::string, DeserializationValue> Capabilities;
        std::map<std::string, DeserializationValue> Settings;
    };

    // #endregion

    // #region TestResult Data Objects

    /**
     * @struct TestDataMetrics
     *
     * @brief The Metrics is a container of a dictionary of MetricData.
     */
    struct TestDataMetrics
    {
        std::map<std::string, SerializationValue> MetricData;
    };

    /**
     * @struct TestDataStepResults
     *
     * @brief The StepResults is a container of a vector of Metrics and map of OtherData.
     */
    struct TestDataStepResults
    {
        std::vector<TestDataMetrics> Metrics;
        std::map<std::string, SerializationValue> OtherData;
        std::map<std::string, SerializationValue> PageResults;
    };

    /**
     * @struct TestDataMonitorResults
     *
     * @brief The MonitorResults is a container of a vector of StepResults and map of OtherData.
     */
    struct TestDataMonitorResults
    {
        std::vector<TestDataStepResults> StepResults;
        std::map<std::string, SerializationValue> OtherData;
    };

    /**
     * @struct TestDataTestResults
     *
     * @brief The TestResults is a container of a vector of MonitorResults and map of OtherData.
     */
    struct TestDataTestResults
    {
        std::vector<TestDataMonitorResults> MonitorResults;
        std::map<std::string, SerializationValue> OtherData;
    };

    // #endregion
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERNAL_SERIALIZABLEDATAMODELS_HPP
