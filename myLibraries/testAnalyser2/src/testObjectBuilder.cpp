/*!
 * @brief Implementation for the testfile object builder
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 03/01/19
 *
 * @todo There may be an issue in what stage i'm doiung things with the do..while
 * loops investigate tomorrow - left while working on _handleOperation
 */

#include "analysisException.h"

#include "testObjectBuilder.h"

namespace testAnalyser2
{

TestObjectBuilder::TestObjectBuilder(TestFile& testfile_in
                                     , std::string filePath)
    : _testfile(testfile_in)
      , _parser(std::make_unique<RapidAbstract>(filePath))
{
    _SetupEnums();
}

TestObjectBuilder::TestObjectBuilder(TestFile& testfile_in
                                     , std::unique_ptr<RapidAbstract> parser_in)
    : _testfile(testfile_in)
      , _parser(std::move(parser_in))
{
    _SetupEnums();
}
/*!
 * @brief Setsup the enum to string handlers
 */
void TestObjectBuilder::_SetupEnums()
{
    _SetupNodeEnums();
    _SetupAttrEnums();
}
/*!
 * @brief The toplevel node (<testcase>)
 */
void TestObjectBuilder::_TopLevelNode()
{
    const char* nodeName_str = nullptr;
    do
    {
        nodeName_str = _parser->GetCurrentNodeName();

        if (nodeName_str)
        {
            nodes_e nodeName = _nodeEnums.getValue(nodeName_str);
            switch (nodeName)
            {
                case nodes_e::NODE_DATAPOINT:
                    _DataPointNode();
                    break;
                case nodes_e::NODE_CONFIG:
                    _ConfigurationNode();
                    break;
                default:
                    throw analyserNodeInWrongPlace_Exception(""
                                                             , 0);
            }
        }
    } while (nodeName_str);
}
/*!
 * @brief Top of a datapoint, gets the data and passes into the dp child nodes
 */
void TestObjectBuilder::_DataPointNode()
{
    /* If we've moved to a child node */
    if (_parser->MoveToChild())
    {
        dataPoint newDP;
        do
        {
            switch (_parser->GetCurrentNodeType())
            {
                /* The data point string*/
                case rapidxml::node_data:
                    newDP._dataPoint = _parser->GetNodeValue();
                    break;
                case rapidxml::node_element:
                    _DataPointChild(newDP);
                    break;
                default:
                    throw analyserIncorrectXMLType_Exception(_parser->GetCurrentNodeName()
                                                             , std::strlen(_parser->GetCurrentNodeName()));
            }
        } while (_parser->MoveToNextNode());

        _testfile.AddDataPoint(newDP);
        _parser->ExitChild();
    }
}
/*!
 * @brief Sorts out the datapoint child nodes.
 */
void TestObjectBuilder::_DataPointChild(dataPoint& dp)
{

    const char* nodeName_str = nullptr;
    do
    {
        nodeName_str = _parser->GetCurrentNodeName();
        if (nodeName_str)
        {
            nodes_e nodeName = _nodeEnums.getValue(nodeName_str);
            switch (nodeName)
            {
                case nodes_e::NODE_OPERATION:
                    break;
                case nodes_e::NODE_VARIABLE:
                    break;
                default:
                    break;
            }
        }
    } while (_parser->MoveToNextNode());
}
/*!
 * @brief Top of a configuration node
 */
void TestObjectBuilder::_ConfigurationNode()
{
    /* If we've moved to a child node */
    if (_parser->MoveToChild())
    {
        testConfiguration newConfiguration;
        do
        {
            switch (_parser->GetCurrentNodeType())
            {
                case rapidxml::node_element:
                    _ConfigurationChild(newConfiguration);
                    break;
                default:
                    throw analyserIncorrectXMLType_Exception(_parser->GetCurrentNodeName()
                                                             , std::strlen(_parser->GetCurrentNodeName()));
            }
        } while (_parser->MoveToNextNode());

        _testfile.AddConfiguration(newConfiguration);
    }
    _parser->ExitChild();
}
/*!
 * @brief Handles all the configuration child nodes
 * @param conf A referencee to the tesConfiguration we're editing
 */
void TestObjectBuilder::_ConfigurationChild(testConfiguration& conf)
{
}
/*!
 * @brief Registers the node enums
 */
void TestObjectBuilder::_SetupNodeEnums()
{
    _nodeEnums.RegisterEnum("dataPoint"
                            , nodes_e::NODE_DATAPOINT);
    _nodeEnums.RegisterEnum("config"
                            , nodes_e::NODE_CONFIG);
    _nodeEnums.RegisterEnum("variable"
                            , nodes_e::NODE_VARIABLE);
    _nodeEnums.RegisterEnum("operation"
                            , nodes_e::NODE_OPERATION);
    _nodeEnums.RegisterEnum("protocol"
                            , nodes_e::NODE_PROTOCOL);
    _nodeEnums.RegisterEnum("rate"
                            , nodes_e::NODE_RATE);
    _nodeEnums.RegisterEnum("chaos"
                            , nodes_e::NODE_CHAOS);
    _nodeEnums.RegisterEnum("duration"
                            , nodes_e::NODE_DURATION);
    _nodeEnums.RegisterEnum("threads"
                            , nodes_e::NODE_THREADS);
    _nodeEnums.RegisterEnum("testName"
                            , nodes_e::NODE_TESTNAME);
    _nodeEnums.RegisterEnum("threadsPerInterface"
                            , nodes_e::NODE_THREADSPERINTERFACE);
}
/*!
 * @brief Registers the attribute enums
 */
void TestObjectBuilder::_SetupAttrEnums()
{
    _attributeEnums.RegisterEnum("protocol"
                                 , attributes_e::ATTR_PROTOCOL);
    _attributeEnums.RegisterEnum("tps"
                                 , attributes_e::ATTR_TPS);
    _attributeEnums.RegisterEnum("multiplier"
                                 , attributes_e::ATTR_MULTIPLIER);
    _attributeEnums.RegisterEnum("seconds"
                                 , attributes_e::ATTR_SECONDS);
    _attributeEnums.RegisterEnum("max"
                                 , attributes_e::ATTR_MAXTHREADS);
    _attributeEnums.RegisterEnum("name"
                                 , attributes_e::ATTR_NAME);
    _attributeEnums.RegisterEnum("action"
                                 , attributes_e::ATTR_ACTION);
    _attributeEnums.RegisterEnum("value"
                                 , attributes_e::ATTR_VALUE);
    _attributeEnums.RegisterEnum("storedIn"
                                 , attributes_e::ATTR_STOREDIN);
    _attributeEnums.RegisterEnum("tpi"
                                 , attributes_e::ATTR_TPI);
}
/*!
 * @brief Handles datapoint operation nodes
 * @return The new operation
 */
testOperation TestObjectBuilder::_handleOperation()
{
    do
    {
        attributes_e attr = _attributeEnums.getValue(_parser->GetCurrentNodeName());
    }
    return testOperation();
}
/*!
 * @brief Handles datapoint variable nodes
 * @return The new variable
 */
testVariable TestObjectBuilder::_handleVariable()
{
    return testVariable();
}
} /* namespace testAnalyser2 */