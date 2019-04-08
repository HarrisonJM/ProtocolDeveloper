/*!
 * @brief Implementation for the GMT Offset handling in the TimeTicker class
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */

#include "gMTHandler.h"
#include "timeTicker/timeTickerDefinitions.h"

namespace timeTicker
{
/*!
 * @brief Normal constructor, uses default wrappers
 */
GMTHandler::GMTHandler()
    : _stdlibModule(std::make_unique<cFunctions::cStdLib>())
      , _stdioModule(std::make_unique<cFunctions::cStdio>())
{
}
/*!
 * @brief Testing/non-std functions constructor
 * @param stdlibModule An unq_p to a stdLib (or similiar) module
 * @param stdioModule An unq_p to an stdio (or similiar) module
 */
GMTHandler::GMTHandler(std::unique_ptr<cFunctions::cStdLib> stdlibModule
                       , std::unique_ptr<cFunctions::cStdio> stdioModule)
    : _stdlibModule(std::move(stdlibModule))
      , _stdioModule(std::move(stdioModule))
{
}
/*!
 * @brief Finds the GMT offset and then prints it to the provided buffer
 * @param theTimeTM_p A pointer to The current time
 * @param buffer_p Where to store the printed offset
 * @param length
 * @return The number of bytes printed
 */
int GMTHandler::PrintGMTOffset(const TT_tm_t* theTimeTM_p
                               , char* buffer_p
                               , size_t length) const
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
/*!
 * @brief Gets the GMT Offset and stores it in offset_p
 * @param tm_p A tim struct ptr that contains the time
 * @param offset_p Where to store the offset
 * @return false on failure
 */
TTRetCode_E GMTHandler::GetGMTOffset(const TT_tm_t* tm_p
                                     , TTGMTOffset_t* offset_p) const
{
    if (!tm_p)
    {
        return TTRetCode::TT_RC_FAILURE;
    }

    if (!offset_p)
    {
        return TTRetCode::TT_RC_FAILURE;
    }

    offset_p->hours = 0;
    offset_p->minutes = 0;
    offset_p->totalSeconds = 0;

    offset_p->minutes = static_cast<int>((tm_p->tm_gmtoff%3600)/60);
    offset_p->hours = static_cast<int>((tm_p->tm_gmtoff/3600));

    offset_p->totalSeconds = (offset_p->hours*TT_SECS_PER_HOUR) +
        (offset_p->minutes*TT_SECS_PER_MIN);

    return TTRetCode::TT_RC_SUCCESS;
}

} /* namespace timeTicker */