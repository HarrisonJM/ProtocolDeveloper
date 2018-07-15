/*!
 * @brief Top-level class that returns a data emitter
 *
 * @addtogroup testCaseHandler
 *
 * @date 04/Jul/2018
 */


#ifndef PROTOCOLDEVELOPER_TESTCASECOMPILER_H
#define PROTOCOLDEVELOPER_TESTCASECOMPILER_H

#include <string>

#include "dataEmitter.h"
#include "dataPoint.h"
#include "testCaseParser.h"
#include "S_testCaseConfiguration.h"

namespace testCaseHandler
{

class TestCaseCompiler
{
public:
    TestCaseCompiler(std::string testCaseName_in);
    ~TestCaseCompiler();

    void doCompilation();

private:
    bool _successful;
    TestCaseParser _parser;
    S_testCaseConfiguration _config;
    DataEmitter _emitter;

    void _HandleNodeSwitch(std::string &nodeName);

    void _HandleDataPoint();
    void _HandleVariable();
    void _HandleOperation();

    void _HandleConfig();

    void _handleSiblings(DataPoint &dataPoint);
    void _handleSiblings(S_testCaseConfiguration &config);

    void _handleDataPointPatternData(DataPoint &dataPoint);
    void _handleDataPointSibling();

};

}
#endif /*PROTOCOLDEVELOPER_TESTCASECOMPILER_H*/
