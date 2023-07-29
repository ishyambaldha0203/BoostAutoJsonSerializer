/*************************************************************************************************
 * @file IJsonDataValidator.hpp
 *
 * @brief Interface to define member contracts to validate the stringified JSON data format.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATAVALIDATOR_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATAVALIDATOR_HPP

#include "CommonConfig.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Interfaces
{
    /**
     * @interface IJsonDataValidator
     *
     * @brief Interface to define member contracts and operations to validate stringified JSON data.
     */
    interface IJsonDataValidator
    {
        DECLARE_INTERFACE_DEFAULTS(IJsonDataValidator)

        /**
         * @brief Validate the provided data, mainly format of data.
         *
         * @param[in] payload A data to be validated.
         *
         * @throw XInvalidFormat On failure of data format validation.
         */
        virtual void Validate(const std::string& payload) = 0;
    };
} // namespace Interfaces
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATAVALIDATOR_HPP