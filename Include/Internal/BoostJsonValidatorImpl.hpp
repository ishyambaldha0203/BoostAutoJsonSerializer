/*************************************************************************************************
 * @file BoostJsonValidatorImpl.hpp
 *
 * @brief Declarations for the concrete class @ref BoostJsonValidatorImpl.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_BOOSTJSONVALIDATORIMPL_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_BOOSTJSONVALIDATORIMPL_HPP

#include "CommonConfig.hpp"

#include "Interfaces/IJsonDataValidatorImpl.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    /**
     * @class BoostJsonValidatorImpl
     *
     * @brief Concrete implementation of underlying impl layer of Json data validator.
     */
    class BoostJsonValidatorImpl : public Interfaces::IJsonDataValidatorImpl
    {
    public:
        // #region Construction/Destruction

        /**
         * @brief  Construct a new implementation layer object of boost json data validator.
         */
        BoostJsonValidatorImpl();

        /**
         * @brief  Destroy implementation layer object of boost json data validator.
         */
        virtual ~BoostJsonValidatorImpl() override;

        // #endregion

        // #region IJsonDataValidatorImpl Implementation

        /**
         * @brief It validates the stringified JSON payload w.r.t formatting.
         *
         * @param payload Json payload to be validated.
         * 
         * @throw XInvalidFormat If the payload is not proper json format. 
         */
        virtual void Validate(const std::string& payload) override;

        // #endregion

    private:
        DECLARE_NON_COPYABLE_CLASS(BoostJsonValidatorImpl)
    };
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERNAL_BOOSTJSONVALIDATORIMPL_HPP
