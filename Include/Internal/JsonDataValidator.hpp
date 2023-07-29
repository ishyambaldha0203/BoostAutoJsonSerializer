/*************************************************************************************************
 * @file JsonDataValidator.hpp
 *
 * @brief Declarations for the concrete class @ref JsonDataValidator.
 *
 *************************************************************************************************/
#ifndef _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATAVALIDATOR_HPP
#define _BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATAVALIDATOR_HPP

#include "CommonConfig.hpp"

#include "Interfaces/IJsonDataValidator.hpp"
#include "Interfaces/IJsonDataValidatorImpl.hpp"

BEGIN_BOOST_AUTO_JSON_SERIALIZER_NS
namespace Internal
{
    /**
     * @class JsonDataValidator
     *
     * @brief Concrete implementation of input JSON data validator.
     */
    class JsonDataValidator : public Interfaces::IJsonDataValidator
    {
    public:
        // #region Construction/Destruction

        /**
         * @brief Construct a new test config validator object.
         *
         * @param[in] impl An instance of underlying implementation layer.
         *
         * @throw XArgumentNullException If input params are null.
         */
        explicit JsonDataValidator(std::shared_ptr<Interfaces::IJsonDataValidatorImpl> impl);

        /**
         * @brief Destroy the test config validator object.
         */
        virtual ~JsonDataValidator() override;

        // #endregion

        // #region ITestSettingProcessor Implementation

        virtual void Validate(const std::string& payload) override;

        // #endregion

    private:
        DECLARE_NON_COPYABLE_CLASS(JsonDataValidator)

        // #region Private Members

        /**
         * @brief An instance of underlying implementation layer of data validator.
         */
        std::shared_ptr<Interfaces::IJsonDataValidatorImpl> _impl;

        // #endregion
    };
} // namespace Internal
END_BOOST_AUTO_JSON_SERIALIZER_NS

#endif // !_BOOST_AUTO_JSON_SERIALIZER_INTERNAL_JSONDATAVALIDATOR_HPP
