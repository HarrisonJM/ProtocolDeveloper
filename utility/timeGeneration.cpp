#include "timeGeneration.h"
#include <string>
#include <sstream>

#include <iostream>

namespace Utility {

    std::wstring GenerateCurrentTimeString()
    {
        //! \TODO: This
        return L"16:04:59.999999";
    }

    std::wstring GenerateCurrentDate()
    {
        //! \TODO: This
        return L"07/12/2017";
    }

    std::wstring GenerateTimeStamp()
    {
        std::wstringstream timeStamp;
        timeStamp << L'[' << GenerateCurrentTimeString()
            << "]["
            << GenerateCurrentDate()
            << ']';

        return timeStamp.str();
    }
}
