#ifndef __FREEFUNCTIONINTERFACES_H__
#define __FREEFUNCTIONINTERFACES_H__

// This class acts as a mocking interface for Gmock that will be used to use mocks of some of the
// free functions included as a part of the software. For example "GetLogSeverity" does not belong
// to any particular class. And while it's used very infrequently, it's used here to start keeping
// Things as organised as possible
class freeFunctionInterfaces
{
    virtual std::wstring GetLogSeverity(LOGSEVERITY_T logSev) = 0;
};

#endif /* __FREEFUNCTIONINTERFACES_H__ */