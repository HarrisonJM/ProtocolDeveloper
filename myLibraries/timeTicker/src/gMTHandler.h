/*!
 * @brief Handles GMTOffset functions in the TimeTicker
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */


#ifndef PROTOCOLDEVELOPER_GMTHANDLER_H
#define PROTOCOLDEVELOPER_GMTHANDLER_H

#include <ctime>
#include <memory>

#include <freeFunctionsAndWrappers/cStdLib.h>
#include <freeFunctionsAndWrappers/cStdio.h>
#include <timeTicker/timeTickerCommon.h>

#include <I_gMTHandler.h>

namespace timeTicker
{

class GMTHandler : public I_gMTHandler
{
public:
    GMTHandler();
    GMTHandler(std::unique_ptr<cFunctions::cStdLib> stdlibModule
                   , std::unique_ptr<cFunctions::cStdio> stdioModule);
    ~GMTHandler() = default;
    int PrintGMTOffset(const struct tm* theTimeTM_p
                       , char* buffer_p
                       , size_t length) const override;
    TTRetCode_E GetGMTOffset(const struct tm* tm_p
                             , TTGMTOffset_t* offset_p) const override ;
private:

    /* Wrappers for C functions */
    std::unique_ptr<cFunctions::I_cStdLib> _stdlibModule;
    std::unique_ptr<cFunctions::I_cStdio> _stdioModule;
};

} /* timeTicker */

#endif /* PROTOCOLDEVELOPER_GMTHANDLER_H */
