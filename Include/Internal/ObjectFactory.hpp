/*************************************************************************************************
 * @file ObjectFactory.hpp
 *
 * @brief Declarations for the concrete class @ref ObjectFactory.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_OBJECTFACTORY_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_OBJECTFACTORY_HPP

#include "CommonConfig.hpp"

#include "Interfaces/Factories/IObjectFactories.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    /**
     * @class ObjectFactory
     *
     * @brief Concrete implementation of main object factory.
     */
    class ObjectFactory : public FactoryInterfaces::IProgramFactory,
                          public FactoryInterfaces::IJsonDataSerializerFactory,
                          public FactoryInterfaces::IJsonDataSerializerImplFactory,
                          public FactoryInterfaces::IJsonDataValidatorFactory,
                          public FactoryInterfaces::IJsonDataValidatorImplFactory,
                          public std::enable_shared_from_this<ObjectFactory>
    {
        // #region Type Aliases

        using ProgramFactoryInterfacePtr = FactoryInterfaces::IProgramFactory::InterfaceSharedPointer;
        using JsonDataSerializerFactoryInterfacePtr = FactoryInterfaces::IJsonDataSerializerFactory::InterfaceSharedPointer;
        using JsonDataSerializerImplFactoryInterfacePtr = FactoryInterfaces::IJsonDataSerializerImplFactory::InterfaceSharedPointer;
        using JsonDataValidatorFactoryInterfacePtr = FactoryInterfaces::IJsonDataValidatorFactory::InterfaceSharedPointer;
        using JsonDataValidatorImplFactoryInterfacePtr = FactoryInterfaces::IJsonDataValidatorImplFactory::InterfaceSharedPointer;

        // #endregion

    public:
        // #region Construction/Destruction

        /**
         * @brief Construct a new Factory object
         */
        ObjectFactory();

        /**
         * @brief Destroy the Object Factory object
         */
        virtual ~ObjectFactory() override;

        // #endregion

        // #region Implementation of Factories

        virtual void Create(ProgramFactoryInterfacePtr &objectPtr) override;

        virtual void Create(JsonDataSerializerFactoryInterfacePtr &objectPtr) override;

        virtual void Create(JsonDataSerializerImplFactoryInterfacePtr &objectPtr) override;

        virtual void Create(JsonDataValidatorFactoryInterfacePtr &objectPtr) override;

        virtual void Create(JsonDataValidatorImplFactoryInterfacePtr &objectPtr) override;

        // #endregion

    private:
        DECLARE_NON_COPYABLE_CLASS(ObjectFactory)

        // #region Private Members

        /**
         * @brief This is to inject the common factory through constructor of all the other required classes.
         *
         * @return The shared pointer of ObjectFactory itself.
         */
        std::shared_ptr<ObjectFactory> Self();

        // #endregion
    };
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERNAL_OBJECTFACTORY_HPP
