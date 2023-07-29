/*************************************************************************************************
 * @file IObjectFactories.hpp
 *
 * @brief Provides abstract factory for all the classes to create a concrete class instance.
 *
 *************************************************************************************************/

#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_FACTORIES_IOBJECTFACTORIES_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERFACES_FACTORIES_IOBJECTFACTORIES_HPP

#include "CommonConfig.hpp"

#include "Interfaces/Factories/IGenericObjectFactoryT.hpp"

#include "Interfaces/IProgram.hpp"
#include "Interfaces/IJsonDataSerializer.hpp"
#include "Interfaces/IJsonDataSerializerImpl.hpp"
#include "Interfaces/IJsonDataValidator.hpp"
#include "Interfaces/IJsonDataValidatorImpl.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace FactoryInterfaces
{
    // #region Functional Classes Factories

    /**
     * @interface IProgramFactory
     *
     * @brief Factory interface for concrete classes that implements @ref IProgram.
     */
    using IProgramFactory = IGenericObjectFactoryT<Interfaces::IProgram>;

    /**
     * @interface IJsonDataSerializerFactory
     *
     * @brief Factory interface for concrete classes that implements @ref IJsonDataSerializer.
     */
    using IJsonDataSerializerFactory = IGenericObjectFactoryT<Interfaces::IJsonDataSerializer>;

    /**
     * @interface IJsonDataSerializerImplFactory
     *
     * @brief Factory interface for concrete classes that implements @ref IJsonDataSerializerImpl.
     */
    using IJsonDataSerializerImplFactory = IGenericObjectFactoryT<Interfaces::IJsonDataSerializerImpl>;

        /**
     * @interface ITestSettingValidatorFactory
     *
     * @brief Factory interface for concrete classes that implements @ref ITestSettingValidator.
     */
    using IJsonDataValidatorFactory = IGenericObjectFactoryT<Interfaces::IJsonDataValidator>;

    /**
     * @interface IJsonDataValidatorImplFactory
     *
     * @brief Factory interface for concrete classes that implements @ref IJsonDataValidatorImpl.
     */
    using IJsonDataValidatorImplFactory = IGenericObjectFactoryT<Interfaces::IJsonDataValidatorImpl>;

    // #endregion

} // namespace FactoryInterfaces
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERFACES_FACTORIES_IOBJECTFACTORIES_HPP
