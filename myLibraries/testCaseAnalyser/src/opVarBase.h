/*!
 * @brief
 *
 * @addtogroup
 *
 * @date 01/10/18
 */


#ifndef PROTOCOLDEVELOPER_OPVARBASE_H
#define PROTOCOLDEVELOPER_OPVARBASE_H

#include <string>

namespace testCaseHandler
{

class OpVarBase
{
public:
    OpVarBase(std::string name,
              std::string specialization,
              std::string value);
    ~OpVarBase();

    std::string getName();
    std::string getValue();

protected:
    std::string _getSpecialization();

private:
    const std::string _name;
    const std::string _specialization;
    std::string _value;
};

} /* namespace testCaseAnalyser*/

#endif /*PROTOCOLDEVELOPER_OPVARBASE_H*/
