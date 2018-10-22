/*!
 * @brief
 *
 * @addtogroup
 *
 * @date 01/10/18
 */



#include "opVarBase.h"

namespace testCaseHandler
{

OpVarBase::OpVarBase(std::string name,
                     std::string specialization,
                     std::string value)
    : _name(std::move(name))
      , _specialization(std::move(specialization))
      , _value(std::move(value))
{

}

/*!
 * @brief Getter, _name
 * @return The name of the entry
 */
std::string OpVarBase::getName()
{
    return _name;
}
/*!
 * @brief Getter, _action
 * @return The specialization that this performs
 */
std::string OpVarBase::_getSpecialization()
{
    return _specialization;
}
/*!
 * @brief Getter, _value
 * @return The value needed
 */
std::string OpVarBase::getValue()
{
    return _value;
}

} /* namespace testCaseHandler */