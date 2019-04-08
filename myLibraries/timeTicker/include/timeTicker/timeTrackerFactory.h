/*!
 * @brief Defines the factory that we'll use to create/export the Concrete TimeTicker
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */


#ifndef PROTOCOLDEVELOPER_TIMETRACKERFACTORY_H
#define PROTOCOLDEVELOPER_TIMETRACKERFACTORY_H

#include <future>
#include "I_TimeTicker.h"

namespace timeTicker
{
/*!
 * @brief Selects the type of timer one would like
 * @{
 */
typedef enum TimePrec
    : short
{
    SECONDS, //! < Uses
    MICRO,
    NANO
} TimePrec_E;
/*!@}*/

class TimeTickerFactory
{
public:
    TimeTickerFactory();
    ~TimeTickerFactory();

    template<typename T, typename ...Args>
    auto GetTimeTicker(T &&t
                       , Args &&... args) -> decltype(t(args...))
    {
        return '1';
    }

private:
};
} /* timeTicker */

#endif /* PROTOCOLDEVELOPER_TIMETICKERFACTORY_H */
