/*!
 * @brief Implementation for the GMT Offset handling in the TimeTicker class
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */

#include <cstdio>
#include <cstdlib>

#include "gMTHandler.h"
#include "timeTickerDefinitions.h"

namespace TimeTicker
{

GMTHandler::GMTHandler(std::unique_ptr<cFunctions::I_cStdLib> stdlibModule
                       , std::unique_ptr<cFunctions::I_cStdio> stdioModule)
    : _stdlibModule(std::move(stdlibModule))
      , _stdioModule(std::move(stdioModule))
{
}

int GMTHandler::PrintGMTOffset(const timeM_t* theTimeTM_p
                               , char* buffer_p
                               , size_t length)
{
    int gmtOffset, hours, minutes, numPrinted;

    // Get the offset
    gmtOffset = static_cast<int>(theTimeTM_p->tm_gmtoff);

    if (0 == gmtOffset)
    {
        numPrinted = _stdioModule->snprintf(buffer_p
                                            , length
                                            , "Z");
    }
    else
    {
        char sign = (gmtOffset > 0) ? '+' : '-';

        gmtOffset = _stdlibModule->abs(gmtOffset);
        ldiv_t result = _stdlibModule->ldiv(gmtOffset
                                            , TT_SECS_PER_HOUR);

        hours = static_cast<int>(result.quot);
        minutes = static_cast<int>(result.rem/TT_SECS_PER_MIN);

        numPrinted = _stdioModule->snprintf(buffer_p
                                            , length
                                            , "%c%02d%02d"
                                            , sign
                                            , hours
                                            , minutes);
    }

    return numPrinted;
}
int GMTHandler::GetGMTOffset(const timeM_t* tm_p
                             , TTGMTOffset_t* offset_p)
{
    if (!tm_p)
    {
        return -1;
    }

    if (!offset_p)
    {
        return -1;
    }

    offset_p->hours = 0;
    offset_p->minutes = 0;
    offset_p->totalSeconds = 0;

    offset_p->minutes = static_cast<int>((tm_p->tm_gmtoff%3600)/60);
    offset_p->hours = static_cast<int>((tm_p->tm_gmtoff/3600));

    offset_p->totalSeconds = (offset_p->hours*TT_SECS_PER_HOUR) +
        (offset_p->minutes*TT_SECS_PER_MIN);

    return 0;
}
} /* namespace TimeTicker */