/*************************************************************************************************
 * @file Program.cpp
 *
 * @brief Concrete implementation of @ref Program class.
 *
 * It handles all the start-up rituals.
 *
 *************************************************************************************************/

#include "Internal/Program.hpp"

#include "Exceptions/XArgumentNull.hpp"

// #region Namespace Symbols

using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Interfaces;
using namespace BOOST_AUTO_JSON_SERIALIZER_NS::Exceptions;

// #endregion

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    // #region Construction/Destruction

    Program::Program() = default;

    Program::~Program() = default;

    // #endregion

    // #region Public Methods

    int32_t Program::Run()
    {

        try
        {
            std::cout << "**** Boost JSON Serializer ****\n"
                      << std::endl;
        }
        catch (const std::exception &ex)
        {
            std::cout << "Exception caught: " << ex.what() << std::endl;

            return -1;
        }

        return 0;
    }

    // #endregion

} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS