/*************************************************************************************************
 * @file ObjectFactory.cpp
 *
 * @brief Concrete implementation of a common object factory.
 *
 * It manages creation and lifespan of all the higher level object of the library.
 *
 *************************************************************************************************/

#include "Internal/ObjectFactory.hpp"

#include "Internal/Program.hpp"
#include "Internal/BoostJsonSerializerImpl.hpp"
#include "Internal/BoostJsonValidatorImpl.hpp"
#include "Internal/JsonDataSerializer.hpp"
#include "Internal/JsonDataValidator.hpp"

// #region Namespace Symbols

using namespace BOOST_AUTO_JSON_SERIALIZER_NS::FactoryInterfaces;

// #endregion

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    // #region Construction/Destruction

    ObjectFactory::ObjectFactory() = default;

    ObjectFactory::~ObjectFactory() = default;

    // #endregion

    // #region Public Methods

    void ObjectFactory::Create(IProgramFactory::InterfaceSharedPointer &objectPtr)
    {
        objectPtr = std::make_shared<Program>();
    }

    void ObjectFactory::Create(IJsonDataSerializerFactory::InterfaceSharedPointer& objectPtr)
    {
        IJsonDataSerializerImplFactory::InterfaceSharedPointer dataSerializerImpl;
        Create(dataSerializerImpl);

        objectPtr = std::make_shared<JsonDataSerializer>(dataSerializerImpl);
    }

    void ObjectFactory::Create(IJsonDataSerializerImplFactory::InterfaceSharedPointer& objectPtr)
    {
        objectPtr = std::make_shared<BoostJsonSerializerImpl>();
    }

    void ObjectFactory::Create(IJsonDataValidatorFactory::InterfaceSharedPointer& objectPtr)
    {
        IJsonDataValidatorImplFactory::InterfaceSharedPointer dataValidatorImpl;
        Create(dataValidatorImpl);

        objectPtr = std::make_shared<JsonDataValidator>(dataValidatorImpl);
    }

    void ObjectFactory::Create(IJsonDataValidatorImplFactory::InterfaceSharedPointer& objectPtr)
    {
        objectPtr = std::make_shared<BoostJsonValidatorImpl>();
    }

    // #endregion

    // #region Private Methods

    std::shared_ptr<ObjectFactory> ObjectFactory::Self()
    {
        return std::enable_shared_from_this<ObjectFactory>::shared_from_this();
    }

    // #endregion
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS
