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

namespace TimeTicker
{

class TimeTickerFactory
{
public:
    TimeTickerFactory();
    ~TimeTickerFactory();

    template<typename T, typename ...Args>
    auto GetTimeTicker(T &&t
                       , Args &&... args) -> decltype(t(args...))
    {

    }

private:
};
} /* TimeTicker */

#endif /* PROTOCOLDEVELOPER_TIMETICKERFACTORY_H */
