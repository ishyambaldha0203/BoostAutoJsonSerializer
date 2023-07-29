/*************************************************************************************************
 * @file XSerialization.hpp
 *
 * @brief Contains concrete definition of XSerialization.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_EXCEPTIONS_XSERIALIZATION_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_EXCEPTIONS_XSERIALIZATION_HPP

#include "Exceptions/XBaseException.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Exceptions
{
    /**
     * @class XSerialization
     *
     * @brief Exception for all the errors related to serialization.
     */
    class XSerialization : public XBaseException
    {
    public:
        /**
         * @brief Use the XBaseException c'tor.
         */
        using XBaseException::XBaseException;
    };
} // namespace Exceptions
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_EXCEPTIONS_XSERIALIZATION_HPP