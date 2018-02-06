#include "TimeGeneration.h"
#include <sstream>
#include <iostream>

namespace Utility {

    std::string GenerateCurrentTimeString()
    {
        //! \TODO: This
        return "16:04:59.999999";
    }

    std::string GenerateCurrentDate()
    {
        //! \TODO: This
        return "07/12/2017";
    }

    std::string GenerateTimeStamp()
    {
        std::stringstream timeStamp;
        timeStamp << '[' << GenerateCurrentTimeString()
            << "]["
            << GenerateCurrentDate()
            << ']';

        return timeStamp.str();
    }
}
