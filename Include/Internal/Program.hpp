/*************************************************************************************************
 * @file Program.hpp
 *
 * @brief Declarations for the concrete class @ref Program.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_PROGRAM_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_PROGRAM_HPP

#include "CommonConfig.hpp"

#include "Interfaces/IProgram.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    /**
     * @class Program
     *
     * @brief Concrete implementation of application start-up class Program.
     */
    class Program : public Interfaces::IProgram
    {
    public:
        // #region Construction/Destruction

        /**
         * @brief Construct a new Program object.
         */
        Program();

        /**
         * @brief Destroy the Program object.
         */
        virtual ~Program() override;

        // #endregion

        // #region IProgram Implementation

        virtual int32_t Run() override;

        // #endregion

    private:
        DECLARE_NON_COPYABLE_CLASS(Program)
    };
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERNAL_PROGRAM_HPP
