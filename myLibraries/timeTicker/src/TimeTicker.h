/*!
 * @brief Declaration for the timeTicker class. Will be used to track the time across the system
 *
 * @author hmarcks
 *
 * @addtogroup timeTicker
 *
 * @date 17/12/18
 */


#ifndef PROTOCOLDEVELOPER_TIMETICKER_H
#define PROTOCOLDEVELOPER_TIMETICKER_H

#include <ctime>
#include <sys/time.h>

namespace TimeTicker
{
//! typedef for the timeval struct
typedef struct timeval timeval_S;

class TimeTicker
{
public:
    TimeTicker();
    ~TimeTicker();
private:
    /*! Used for caching between uses */
    const int _timeStampBufferSize; /* 32 */
    char _timeStampBuffer[32];
    timeval_S _lastTime = {0};
    int _lastHour = -1;


};

} /* TimeTicker */

#endif /*PROTOCOLDEVELOPER_TIMETICKER_H*/
