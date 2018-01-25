#ifndef __FREEFUNCTIONMOCKS_H__
#define __FREEFUNCTIONMOCKS_H__
//DON'T INCLUDE THIS FILE ANYWHERE PLEASE THANK YOU
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "freeFunctionInterfaces.h"

class FreeFunctionMock : public freeFunctionInterfaces
{
public:

    MOCK_METHOD1(GetLogSeverity, std::wstring (LOGSEVERITY_T logSev));
};

#endif /* __FREEFUNCTIONMOCKS_H__ */