/*!
 * @brief Module used to perform basic calculations
 *
 * @addtogroup Utility
 *
 * @date 09/07/18
 */

#ifndef PROTOCOLDEVELOPER_MATHSMODULE_H
#define PROTOCOLDEVELOPER_MATHSMODULE_H

#include <string>

namespace SafeContainers
{

class MathsModule
{
public:
    MathsModule();
    ~MathsModule();

    //! @brief Performs an action on the provided value
    void PerformAction(std::string* value_in
        ,std::string minValue_in
        ,std::string maxValue_in
        ,int action);

private:
    void increment(std::string* value_in
        ,std::string minValue_in
        ,std::string maxValue_in);
    void decrement(std::string* value_in
                   ,std::string minValue_in
                   ,std::string maxValue_in);
    void addToValue(std::string* value_in
                   ,std::string minValue_in
                   ,std::string maxValue_in);
    void subtractFromValue(std::string* value_in
                           ,std::string minValue_in
                           ,std::string maxValue_in);
    void appendToValue(std::string* value_in
                       ,std::string minValue_in
                       ,std::string maxValue_in);
};

}

#endif /*PROTOCOLDEVELOPER_MATHSMODULE_H*/
