/*************************************************************************************************
 * @file IJsonDataValidatorImpl.hpp
 *
 * @brief Contains the interface to define member contracts of implementation layer of @ref IJsonDataValidator.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATAVALIDATORIMPL_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATAVALIDATORIMPL_HPP

#include "CommonConfig.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Interfaces
{
    /**
     * @interface IJsonDataValidatorImpl
     *
     * @brief Interface to define member contracts and operations implementation layer of @ref IJsonDataValidator.
     */
    interface IJsonDataValidatorImpl
    {
        DECLARE_INTERFACE_DEFAULTS(IJsonDataValidatorImpl)

        /**
         * @brief Validate the provided stringified JSON data.
         *
         * @param[in] payload A data to be validated.
         *
         * @throw XInvalidFormat On failure of data format validation.
         */
        virtual void Validate(const std::string& payload) = 0;
    };
} // namespace Interfaces
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IJSONDATAVALIDATORIMPL_HPP