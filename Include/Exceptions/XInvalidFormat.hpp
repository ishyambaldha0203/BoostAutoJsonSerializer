/*************************************************************************************************
 * @file XInvalidFormat.hpp
 *
 * @brief Contains concrete definition of XSerialization.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_EXCEPTIONS_XINVALIDFORMAT_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_EXCEPTIONS_XINVALIDFORMAT_HPP

#include "Exceptions/XBaseException.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Exceptions
{
    /**
     * @class XInvalidFormat
     *
     * @brief Exception for all the errors related to serialization.
     */
    class XInvalidFormat : public XBaseException
    {
    public:
        /**
         * @brief Use the XBaseException c'tor.
         */
        using XBaseException::XBaseException;
    };
} // namespace Exceptions
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_EXCEPTIONS_XINVALIDFORMAT_HPP