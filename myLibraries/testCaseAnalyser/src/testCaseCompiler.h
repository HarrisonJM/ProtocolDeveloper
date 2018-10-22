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
#include "testCaseConfiguration_s.h"

namespace testCaseHandler
{

class TestCaseCompiler
{
public:
    TestCaseCompiler(std::string testCaseName_in);
    ~TestCaseCompiler();

    void CompileXML();

private:
    bool _successful;
    TestCaseParser _parser;
    testCaseConfiguration_s _config;
    DataEmitter _emitter;

    void _HandleNodeSwitch(std::string &nodeName);

    void _HandleDataPoint();
    void _HandleVariable();
    void _HandleOperation();

    void _HandleConfig();

    void _handleSiblings(std::shared_ptr<DataPoint> dataPoint);
    void _handleSiblings(testCaseConfiguration_s &config);

    void _handleDataPointPatternData();

    void _HandleRate();
    void _HandleChaos();
    void _HandleDuration();
    void _HandleThreads();

};

} /* namespace testCaseHandler */

#endif /* PROTOCOLDEVELOPER_TESTCASECOMPILER_H */
