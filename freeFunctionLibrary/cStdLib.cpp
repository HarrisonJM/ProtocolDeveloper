//
// Created by hmarcks on 13/05/18.
//

#include "cStdLib.h"


namespace cFunctions
{

void *cStdLib::cMalloc(size_t __size)
{
    return malloc(__size);
}

}