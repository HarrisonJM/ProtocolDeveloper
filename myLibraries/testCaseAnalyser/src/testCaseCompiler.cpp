/*!
 * @brief "Compiles" the XML into a form that can create data to be used
 *
 * Pumps out a data emitter and a rate struct
 *
 * @addtogroup testCaseHandler
 *
 * @date 04/Jul/2018
 *
 * @todo Output the XML after being tokenized into an
 * intermediate format for faster future parsing
 *
 * @todo perahps create this as a seperate app that can be laucnhed from within
 * the core/CLI
 */

#include <memory>

#include "dataPoint.h"
#include "testCaseCompiler.h"
#include "testCaseException.h"

namespace testCaseHandler
{

TestCaseCompiler::TestCaseCompiler(std::string testCaseName_in) :
    _successful(false)
    ,_parser(testCaseName_in)
    ,_config()
    ,_emitter()
{
    // Use a try catch around this constructor to catch initial parser issues
}

TestCaseCompiler::~TestCaseCompiler()
{

}

void TestCaseCompiler::CompileXML()
{
    do
    {
        std::string entryName;
        _parser.GetCurrentEntryName(entryName);
        _HandleNodeSwitch(entryName);

    }while(_parser.MoveToNextEntry());

    // All done!
}

void TestCaseCompiler::_HandleNodeSwitch(std::string &nodeName)
{
    if ("dataPoint" == nodeName)
        _HandleDataPoint();
    else if ("config" == nodeName)
        _HandleConfig();
    else if ("variable" == nodeName)
        _HandleVariable();
    else if ("operation" == nodeName)
        _HandleOperation();
    else if ("rate" == nodeName)
        _HandleRate();
    else if ("chaos" == nodeName)
        _HandleChaos();
    else if ("duration" == nodeName)
        _HandleDuration();
    else if ("threads" == nodeName)
        _HandleThreads();
    else
        throw parser_badNodeName();
}
void TestCaseCompiler::_HandleDataPoint()
{
    // Holds the entire datapoint we're building
    auto dataPoint = std::make_shared<DataPoint>();
    _emitter.RegisterDataPoint(dataPoint);

    _handleDataPointPatternData();

    try
    {
        _handleSiblings(dataPoint);
    } catch ( testCaseException e ) {
        //! @todo Handle me
        // Bad type! No Type!
    }
}

/*!
 * @brief Handles variable creation for a datapoint
 */
void TestCaseCompiler::_HandleVariable()
{
    _parser.MoveToNextEntry();
    std::string attrName, attrValue;
    std::string name, value, action;

    while(!_parser.GetCurrentEntryAttribute(attrName,
                                            attrValue))
    {
        if ("action" == attrName)
            action = attrValue;
        else if ("value" == attrName)
            value = attrValue;
        else if ("name" == attrName)
            name = attrValue;
    }

    auto newVar = std::make_unique<variable>(variable(name, value, action));
    _emitter.AccessDataPoint(_emitter.getNumberOfDataPoints()-1).RegisterVariable(std::move(newVar));
}

void TestCaseCompiler::_HandleOperation()
{
    //<operation name="terminate" storedIn="Stratum" value="0"/>
    _parser.MoveToNextEntry();
    std::string attrName, attrValue;
    std::string name, value, storedIn;
    int counter = 0;

    while(!_parser.GetCurrentEntryAttribute(attrName,
                                            attrValue))
    {
        if ("storedIn" == attrName)
            storedIn = attrValue;
        else if ("value" == attrName)
            value = attrValue;
        else if ("name" == attrName)
            name = attrValue;

        counter++;
    }

    // Only needs to be reset if all three have been reached because otherwise
    // it'll exit the loop with the method having been reset

    if(3 == counter)
        // Reset
        _parser.GetCurrentEntryAttribute(name,
                                         value);

    auto newOp = std::make_unique<operation>(operation(name, value, storedIn));
    _emitter.AccessDataPoint(_emitter.getNumberOfDataPoints()-1).RegisterOperation(std::move(newOp));
}

void TestCaseCompiler::_HandleConfig()
{
    _parser.MoveToSibling();
    do
    {
        std::string optionName;
        _parser.GetCurrentEntryName(optionName);
        _HandleNodeSwitch(optionName);

    } while(_parser.MoveToNextEntry());
}

/*!
 * @brief Goes through each sibling
 *
 * When this method completes the top level entity (dataPoint) is fully parsed
 *
 * @param dataPoint
 */
void TestCaseCompiler::_handleSiblings(std::shared_ptr<DataPoint> dataPoint)
{
    _parser.MoveToSibling();

    do
    {
        std::string entryName;
        auto nt = _parser.GetEntryType();

        switch(nt)
        {
            // The raw pattern [foo][bar][baz]
            case rapidxml::node_data :
                throw parser_TooManyData();

            // An attribute
            case rapidxml::node_element :
                _parser.GetCurrentEntryName(entryName);
                _HandleNodeSwitch(entryName);
                break;
            default:
                throw parser_badType();
        }
    } while(_parser.MoveToNexTSibling());

    // Return to Top level
    _parser.DoneWithSibling();
}
/*!
 * @brief Goes through each sibling and sets up the configuration class
 *
 * @param config A reference to a config struct class
 */
void TestCaseCompiler::_handleSiblings(testCaseConfiguration_s &config)
{
    _parser.MoveToSibling();

    do
    {
        std::string entryName;
        _parser.GetCurrentEntryName(entryName);
        _HandleNodeSwitch(entryName);

    }while(_parser.MoveToNextEntry());

    // Return to Top level
    _parser.DoneWithSibling();
}
void TestCaseCompiler::_handleDataPointPatternData()
{
    std::string data;
    _parser.GetEntryData(data);
    _emitter.AccessDataPoint(_emitter.getNumberOfDataPoints()-1).setPattern(data);
}
void TestCaseCompiler::_HandleRate()
{
    std::string name, value;
    _parser.GetCurrentEntryAttribute(name,
                                     value);

    std::size_t numberOfCharsProcess;
    _config.rate = std::stoull(value,
                         &numberOfCharsProcess,
                         10);
    // Reset
    _parser.GetCurrentEntryAttribute(name,
                                     value);
}
void TestCaseCompiler::_HandleChaos()
{
    std::string name, value;
    _parser.GetCurrentEntryAttribute(name,
                                     value);

    std::size_t numberOfCharsProcess;
    _config.chaos = std::stoull(value,
                               &numberOfCharsProcess,
                               10);
    // Reset
    _parser.GetCurrentEntryAttribute(name,
                                     value);
}
void TestCaseCompiler::_HandleDuration()
{
    std::string name, value;
    _parser.GetCurrentEntryAttribute(name,
                                     value);

    std::size_t numberOfCharsProcess;
    _config.duration = std::stoull(value,
                                &numberOfCharsProcess,
                                10);
    // Reset
    _parser.GetCurrentEntryAttribute(name,
                                     value);
}
void TestCaseCompiler::_HandleThreads()
{
    std::string name, value;
    _parser.GetCurrentEntryAttribute(name,
                                     value);

    std::size_t numberOfCharsProcess;
    _config.threads = std::stoull(value,
                                &numberOfCharsProcess,
                                10);
    // Reset
    _parser.GetCurrentEntryAttribute(name,
                                     value);
}

// Do compilation
    // get next node
    // is it a keyword

    // keyword: Look for attributes
    //          get data

                // Attribute: save value
    // Build interpreter
        // How does it behave, what does it return
            // Use decltype/auto for vague return type
    // Register interpreter

} /* namespace  testCaseHandler */