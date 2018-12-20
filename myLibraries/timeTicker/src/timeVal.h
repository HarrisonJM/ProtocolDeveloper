/*!
 * @brief Declarations for the Timeval related functions
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */


#ifndef PROTOCOLDEVELOPER_TIMEVAL_H
#define PROTOCOLDEVELOPER_TIMEVAL_H

#include <ctime>
#include <cstdint>

#include <timeTicker/timeTicker.h>
#include "timeTickerDefinitions.h"
#include "timeTicker/timeTickerCommon.h"


namespace TimeTicker
{

class TimeVal : public TimeTicker
{
public:
    TimeVal();
    ~TimeVal() = default;
    const char* getTimeStampMicro() override;
    const char* getTimestampMilli() override;

    const char* getStringMicro(const struct timeval* tv) override;
private:
    /* Used for caching between uses */
    char _timeStampBuffer[TT_TIMEVAL_STR_SIZE];
    timeval_t _lastTime;
    int _lastHour;

//    cFunctions::I_gMTHandler gmtHandler();

    const char* _genTimevalToString(const timeval_t* tv
                                        , size_t numDecimalDigits);
};

} /* TimeTicker */

#endif /* PROTOCOLDEVELOPER_TIMEVAL_H */
