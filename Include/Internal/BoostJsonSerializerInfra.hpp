/*************************************************************************************************
 * @file BoostJsonSerializerInfra.hpp
 *
 * @brief Contains overloaded methods of boost json library required for data serialization.
 *
 * All the methods in here are internally used by 'value_from' and 'value_to' methods of boost.json library
 * for data serialization and deserialization.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_BOOSTJSONSERIALIZERINFRA_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_BOOSTJSONSERIALIZERINFRA_HPP

#include "CommonConfig.hpp"

#include <type_traits>

#include "Internal/SerializableDataModels.hpp"

#include "Exceptions/XSerialization.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    namespace bd = boost::describe;
    namespace bj = boost::json;
    namespace bv2 = boost::variant2;

    // #region Data Model Describer

    /**
     * @brief Describer macros required for automatic to/from json conversion.
     *
     * @warning The describer macro must be placed in the same namespace as the struct.
     *
     * For more details refer,
     * https://www.boost.org/doc/libs/1_80_0/libs/describe/doc/html/describe.html#ref_boost_describe_struct
     */

    BOOST_DESCRIBE_STRUCT(TestDataTestPolicy, (), (Capabilities, Settings))

    BOOST_DESCRIBE_STRUCT(TestDataMetrics, (), (MetricData))

    BOOST_DESCRIBE_STRUCT(TestDataStepResults, (), (Metrics, OtherData, PageResults))

    BOOST_DESCRIBE_STRUCT(TestDataMonitorResults, (), (StepResults, OtherData))

    BOOST_DESCRIBE_STRUCT(TestDataTestResults, (), (MonitorResults, OtherData))

    // #endregion

    // #region Deserialization Infrastructure

    /**
     * @brief Helper extraction function for mapping objects as value types
     *
     * @tparam TElement Type of element being mapped
     * @param[in] obj The object extracting from
     * @param[in] name The name of the object being extracted
     * @param[out] value The extracted value
     */
    template <typename TElement>
    inline void Extract(const bj::object& obj,
                        const char* name,
                        TElement& value)
    {
        value = bj::value_to<TElement>(obj.at(name));
    }

    /**
     * @brief Auto conversion function to convert a value into a TElement type
     *
     * Code reference, https://www.boost.org/doc/libs/1_80_0/libs/describe/doc/html/describe.html#example_to_json
     *
     * Yes, this function _does_ violate our naming guidelines but unfortunately, it must. This is a magic function from Boost
     * and must be named as-is or it will not be detected.
     *
     * @tparam TElement The type to map from
     * @tparam TPublic A helper object to ensure proper functionality on public variables
     * @tparam TPrivate A helper object to ensure private variables are not mapped
     * @tparam std::enable_if_t<boost::mp11::mp_empty<TPrivate>::value && !std::is_union<TElement>::value> A helper to ensure we don't map private variables
     *
     * @param[in] v The value object to map to the TElement
     *
     * @return TElement The mapped object
     */
    template <typename TElement,
              typename TPublic = bd::describe_members<TElement, bd::mod_public | bd::mod_protected>,
              typename TPrivate = bd::describe_members<TElement, bd::mod_private>,
              typename TEnableIf = std::enable_if_t<boost::mp11::mp_empty<TPrivate>::value && !std::is_union<TElement>::value>>
    inline TElement tag_invoke(const bj::value_to_tag<TElement>&, const bj::value& v)
    {
        const bj::object& obj = v.as_object();

        TElement t{};

        boost::mp11::mp_for_each<TPublic>([&](auto D)
                                          { Extract(obj, D.name, t.*D.pointer); });

        return t;
    }

    /**
     * @brief A tag_invoke overload specific to sort out the variant object within DeserializationValue.
     *
     * @param[in] bjValue The boost::json::value object to be mapped with DeserializationVariant.
     * @return DeserializationValue The wrapped variant object.
     *
     * @throw XSerialization on getting unexpected DeserializationValue.
     */
    DeserializationValue inline tag_invoke(bj::value_to_tag<DeserializationValue>, const bj::value& bjValue)
    {
        DeserializationVariant data;

        switch (bjValue.kind())
        {
        case bj::kind::string:
            data = bj::value_to<std::string>(bjValue);
            break;
        case bj::kind::int64:
            data = bj::value_to<int64_t>(bjValue);
            break;
        case bj::kind::uint64:
            data = bj::value_to<uint64_t>(bjValue);
            break;
        case bj::kind::double_:
            data = bj::value_to<double>(bjValue);
            break;
        case bj::kind::bool_:
            data = bj::value_to<bool>(bjValue);
            break;
        case bj::kind::null:
        case bj::kind::object:
        case bj::kind::array:
            throw Exceptions::XSerialization("Unexpected Json value type!");
            break;
        default:
            throw Exceptions::XSerialization("Unknown Json value type!");
            break;
        }

        return DeserializationValue{data};
    }

    // #endregion

    // #region Serialization Infrastructure

    /**
     * @brief Auto conversion function to allow mapping from TElement type into a boost::json::value object
     *
     * Code reference, https://www.boost.org/doc/libs/1_80_0/libs/describe/doc/html/describe.html#example_to_json
     *
     * Yes, this function _does_ violate our naming guidelines but unfortunately, it must. This is a magic function from Boost
     * and must be named as-is or it will not be detected.
     *
     * @tparam TElement The type to map from
     * @tparam TPublic A helper object to ensure proper functionality on public variables
     * @tparam TPrivate A helper object to ensure private variables are not mapped
     * @tparam std::enable_if_t<boost::mp11::mp_empty<TPrivate>::value && !std::is_union<TElement>::value> A helper to ensure we don't map private variables
     *
     * @param[in,out] v The resultant value object
     * @param[in] t The element needing conversion
     */
    template <typename TElement,
              typename TPublic = bd::describe_members<TElement, bd::mod_public | bd::mod_protected>,
              typename TPrivate = bd::describe_members<TElement, bd::mod_private>,
              typename TEnableIf = std::enable_if_t<boost::mp11::mp_empty<TPrivate>::value && !std::is_union<TElement>::value>>
    inline void tag_invoke(const bj::value_from_tag&, bj::value& v, const TElement& t)
    {
        bj::object& obj = v.emplace_object();

        boost::mp11::mp_for_each<TPublic>([&](auto D)
                                          { obj[D.name] = bj::value_from(t.*D.pointer); });
    }

    /**
     * @brief This class provides SerializationValue mapping to a boost::json::value via the variant apply_visitor or visit.
     */
    class SerializationValueVisitor : public boost::static_visitor<bj::value>
    {
    public:
        template <typename T>
        bj::value operator()(const T& val) const { return bj::value(val); }
    };

    /**
     * @brief A tag_invoke overload specific to sorting out the variant object within SerializationValue.
     *
     * @param[out] bjValue The value being retrieved from the variant
     * @param[in] SerializationValue The variant wrapper
     */
    void inline tag_invoke(bj::value_from_tag, bj::value& bjValue, const SerializationValue& SerializationValue)
    {
        bjValue = bv2::visit(SerializationValueVisitor{}, SerializationValue.data);
    }

    // #endregion
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERNAL_BOOSTJSONSERIALIZERINFRA_HPP