/*!
 * @brief Public interface for the Time ticker class
 *
 * @author hmarcks
 *
 * @date 18/12/2018
 *
 * @addtogroup Time Ticker
 */

#ifndef PROTOCOLDEVELOPER_I_TIMETICKER_H
#define PROTOCOLDEVELOPER_I_TIMETICKER_H

#include <ctime>
#include <climits>

namespace TimeTicker
{

class I_TimeTicker
{
public:
    ~I_TimeTicker() = default;
    virtual const char* getTimeStampMicro() = 0;
    virtual const char* getTimestampMilli() = 0;
    virtual const char* getStringMicro(const struct timeval* tv) = 0;
private:
};

} /* namespace TimeTicker */

#endif /* PROTOCOLDEVELOPER_I_TIMETICKER_H */
