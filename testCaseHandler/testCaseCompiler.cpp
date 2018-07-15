/*!
 * @brief "Compiles" the XML into a form that can create data to be used
 *
 * Pumps out a data emitter and a rate struct
 *
 * @addtogroup testCaseHandler
 *
 * @date 04/Jul/2018
 */

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
    // Check parser
    if(!_parser.IsSetup())
        return;
}

void TestCaseCompiler::doCompilation()
{
    std::string information;

    do
    {
        _parser.GetCurrentEntryName(information);
        _HandleNodeSwitch(information);

    }while(_parser.MoveToNextEntry());
}

void TestCaseCompiler::_HandleNodeSwitch(std::string &nodeName)
{
    if ("dataPoint" == nodeName)
        _HandleDataPoint();
    else if ("config" == nodeName)
        _HandleConfig();
}

void TestCaseCompiler::_HandleDataPoint()
{
    // Holds the entire datapoint we're building
    DataPoint dataPoint;

    _handleSiblings(dataPoint);
}

void TestCaseCompiler::_HandleVariable()
{

}

void TestCaseCompiler::_HandleOperation()
{

}

void TestCaseCompiler::_HandleConfig()
{

}

/*!
 * @brief Goes through each sibling
 *
 * When this method completes the top level entity is fully parsed
 * @param dataPoint
 */
void TestCaseCompiler::_handleSiblings(DataPoint &dataPoint)
{
    bool dataGotten = false;
    _parser.MoveToNexToSibling();

    do
    {
        rapidxml::node_type nt = _parser.GetSiblingType();
        switch(nt)
        {
            // The raw pattern [foo][bar][baz]
            case rapidxml::node_data :
                if(!dataGotten)
                {
                    _handleDataPointPatternData(dataPoint);
                }
                else
                    throw parser_TooManyData();

                break;
            // An attribute
            case rapidxml::node_element :
                std::string attributeName;
                _parser.GetCurrentSiblingName(attributeName);
                break;


        }
    }while(_parser.MoveToNexToSibling());
}

/*!
 * @brief Goes through each sibling and sets up the configuration class
 * @param config A reference to a config struct class
 */
void TestCaseCompiler::_handleSiblings(S_testCaseConfiguration &config)
{
    do
    {


    }while(_parser.MoveToNexToSibling());
}

void TestCaseCompiler::_handleDataPointPatternData(DataPoint &dataPoint)
{
    std::string data;
    _parser.GetEntryData(data);
    dataPoint.setPattern(data);
}

void TestCaseCompiler::_handleDataPointSibling()
{
    std::string nodeName;
    _parser.GetCurrentSiblingName(nodeName);
    if(nodeName == "variable")
        _HandleVariable();
    else
        _HandleOperation();
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


} /* CHANGEME */