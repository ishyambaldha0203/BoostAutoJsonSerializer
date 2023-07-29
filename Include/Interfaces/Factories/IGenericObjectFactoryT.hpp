/**********************************************************************
 * @file IGenericObjectFactoryT.hpp
 *
 * @brief Provides generic abstract factory to create concrete class instances all the classes.
 *
 *********************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_FACTORIES_IGENERICOBJECTFACTORYT_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_FACTORIES_IGENERICOBJECTFACTORYT_HPP

#include "CommonConfig.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace FactoryInterfaces
{
    /**
     * @interface IGenericObjectFactoryT
     *
     * @brief Generic class that can be used to define a factory with a simple interface with Just Create.
     *
     * Most of the factories can be implement in this way just by 'using'.
     *
     * It also provides type definition for the pointer to the interface that is useful for creating helpers for templated classes.
     *
     * @tparam TInterface a generic interface.
     */
    template <class TInterface>
    interface IGenericObjectFactoryT
    {
        DECLARE_INTERFACE_DEFAULTS(IGenericObjectFactoryT)

        /**
         * @brief Pointer to the interface that is the output of the factory.
         */
        using InterfaceSharedPointer = std::shared_ptr<TInterface>;

        /**
         * @brief Create a concrete instance surfaced as pointer to its interfaces
         *
         * The interface is in the parameter so that can be used to change the signature of the Create without adding the name.
         *
         * @param[out] objectPtr pointer to the concrete class object referred through interface.
         */
        virtual void Create(InterfaceSharedPointer& objectPtr) = 0;
    };
} // namespace FactoryInterfaces
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERFACES_FACTORIES_IGENERICOBJECTFACTORYT_HPP
