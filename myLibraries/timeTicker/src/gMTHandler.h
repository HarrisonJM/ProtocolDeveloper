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
#include <I_gMTHandler.h>
#include "timeTicker/timeTickerCommon.h"
#include "../../unitTestUtility/freeFunctionsAndWrappers/include/I_cStdLib.h"
#include "../../unitTestUtility/freeFunctionsAndWrappers/include/I_cStdio.h"
#include <memory>

namespace TimeTicker
{

class GMTHandler : public I_gMTHandler
{
public:
    GMTHandler(std::unique_ptr<cFunctions::I_cStdLib> stdlibModule
                   , std::unique_ptr<cFunctions::I_cStdio> stdioModule);
    ~GMTHandler() = default;
    int PrintGMTOffset(const struct tm* theTimeTM_p
                       , char* buffer_p
                       , size_t length) override;
    int GetGMTOffset(const struct tm* tm_p
                     , TTGMTOffset_t* offset_p) override;
private:

    /* Wrappers for C functions */
    std::unique_ptr<cFunctions::I_cStdLib> _stdlibModule;
    std::unique_ptr<cFunctions::I_cStdio> _stdioModule;
    // cstdio wrapper
};

} /* TimeTicker */

#endif /* PROTOCOLDEVELOPER_GMTHANDLER_H */
