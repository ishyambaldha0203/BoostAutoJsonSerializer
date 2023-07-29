/*************************************************************************************************
 * @file IProgram.hpp
 *
 * @brief Interface to define member contracts for start-up class of application.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IPROGRAM_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IPROGRAM_HPP

#include "CommonConfig.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Interfaces
{
    /**
     * @interface IProgram
     *
     * @brief Interface that represents a program object that synchronously runs a single application.
     */
    interface IProgram
    {
        DECLARE_INTERFACE_DEFAULTS(IProgram)

        /**
         * @brief Synchronously executes the application. When this method returns, the application is
         * considered terminated.
         *
         * @todo Define all possible return values.
         *
         * @return 0 if the application exited normally. Otherwise, a non-zero error code is
         * returned. The exact values are TBD.
         */
        virtual int32_t Run() = 0;
    };
} // namespace Interfaces
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERFACES_IPROGRAM_HPP
