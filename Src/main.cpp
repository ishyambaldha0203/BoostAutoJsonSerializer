/*************************************************************************************************
 * @file main.cpp
 *
 * @brief Starting point of to play with boost auto JSON serializer.
 *
 *************************************************************************************************/

#include "Internal/ObjectFactory.hpp"

// #region Namespace Symbols

using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Internal;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::FactoryInterfaces;

// #endregion

/**
 * @brief Entry-point function to play with boost auto JSON serializer.
 *
 * @return 0 if the service application exited normally. Otherwise, a non-zero error code will
 * be returned.
 */
int main()
{
    // Creat the common object factory that own all the objects created for the application
    std::shared_ptr<ObjectFactory> commonObjectFactory = std::make_shared<ObjectFactory>();

    // Create the program.
    IProgramFactory::InterfaceSharedPointer program;
    commonObjectFactory->Create(program);

    return program->Run();
}