/*!
 * @brief Declaration for the base timeTicker class. All other classes will derive from this one
 *
 * @author hmarcks
 *
 * @addtogroup timeTicker
 *
 * @date 17/12/18
 */


#ifndef PROTOCOLDEVELOPER_TIMETICKER_H
#define PROTOCOLDEVELOPER_TIMETICKER_H

#include "I_TimeTicker.h"
#include "timeTickerCommon.h"
#include "timeTickerDefinitions.h"

#include <ctime>
#include <sys/time.h>
#include <cstdint>
#include <climits>

namespace TimeTicker
{

class TimeTicker : public I_TimeTicker
{
public:
    TimeTicker();
    ~TimeTicker() = default;
    const char* getTimeStampMicro() override;
    const char* getTimestampMilli() override;

    const char* getStringMicro(const struct timeval* tv) override;

private:
    /* Used for caching between uses */
    char _timeStampBuffer[TT_TIMEVAL_STR_SIZE];
    timeval_t _lastTime;
    int _lastHour;

    /* Interfaces for mocking */
//    cFunctions::I_ctime *cTimeImplementation;
//    I_gMTHandler* gMTHandler;

};

} /* TimeTicker */

#endif /*PROTOCOLDEVELOPER_TIMETICKER_H*/
