
#include "gmock/gmock.h"
#include "../I_WorkerThread.h"

#ifndef PROTOCOLDEVELOPER_WORKERTHREADMOCKS_H
#define PROTOCOLDEVELOPER_WORKERTHREADMOCKS_H

class WorkerThreadMocks : class I_WorkerThread
{
    MOCK_METHOD0(run, void());

    //! Workaround for googlemock's inability to mock operator overloading
    MOCK_METHOD0(ROUNDBRACKOP, void());
    virtual void operator()() override { return ROUNDBRACKOP(); }
};

#endif //PROTOCOLDEVELOPER_WORKERTHREADMOCKS_H
