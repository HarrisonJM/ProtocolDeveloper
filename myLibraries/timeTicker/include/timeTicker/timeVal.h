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
#include <memory>

#include <I_gMTHandler.h>
#include <freeFunctionsAndWrappers/cStdio.h>

#include <timeTicker/timeTicker.h>
#include "timeTickerDefinitions.h"
#include "timeTicker/timeTickerCommon.h"

namespace timeTicker
{

class TimeVal
    : public TimeTicker
{
public:
    TimeVal();
    TimeVal(std::unique_ptr<I_gMTHandler> gmtHandler
            , std::unique_ptr<cFunctions::I_cStdio> stdioModule);
    ~TimeVal() = default;
    const char* getTimeStampMicro() override;
    const char* getTimestampMilli() override;
    const char* getStringMicro(const struct timeval* tv) override;

    TTRetCode PrintGeneralizedTime(const TT_tm_t* tm_p
                                   , unsigned int* microsecs_p
                                   , unsigned int fractionDigits
                                   , char* buf_p
                                   , size_t bufSize);
private:
    /* Used for caching between uses */
    char _timeStampBuffer[TT_TIMEVAL_STR_SIZE];
    TT_timeval_t _lastTime;
    int _lastHour;

    std::unique_ptr<I_gMTHandler> _gmtHandler;
    std::unique_ptr<cFunctions::I_cStdio> _stdioModule;

    const char* _genTimevalToString(const TT_timeval_t* tv
                                    , size_t numDecimalDigits);
};
} /* timeTicker */

#endif /* PROTOCOLDEVELOPER_TIMEVAL_H */
