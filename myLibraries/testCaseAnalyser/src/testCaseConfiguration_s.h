

#ifndef PROTOCOLDEVELOPER_TESTCASECONFIGURATION_H
#define PROTOCOLDEVELOPER_TESTCASECONFIGURATION_H

//#include <conf.h>
#include <cinttypes>

struct testCaseConfiguration_s
{
    uint64_t rate;
    uint64_t chaos;
    uint64_t duration;
    uint64_t threads;
};

#endif //PROTOCOLDEVELOPER_TESTCASECONFIGURATION_H
