/*!
 * @brief Declaration for the WallClock class, works exclusively in seconds
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */


#ifndef PROTOCOLDEVELOPER_WALLCLOCK_H
#define PROTOCOLDEVELOPER_WALLCLOCK_H

#include <ctime>

namespace TimeTicker
{

class WallClock
{
public:
    WallClock();
    ~WallClock();
    const char* getTimeToString(time_t theTime);
private:
};
} /* TimeTicker */

#endif /*PROTOCOLDEVELOPER_WALLCLOCK_H*/
