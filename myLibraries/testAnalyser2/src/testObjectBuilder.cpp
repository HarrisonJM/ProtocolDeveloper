/*!
 * @brief Implementation for the testfile object builder
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 03/01/19
 *
 * @todo Refactor variables and operations into their respective classes!
 */

#include "analysisException.h"

#include "testObjectBuilder.h"

namespace testAnalyser2
{
/*!
 * @brief Constructor, uses the default rapidAbstract class
 * @param testfile_in The testfile object that represents the file we're reading in
 * @param filePath The path to the file that we want to open
 */
TestObjectBuilder::TestObjectBuilder(TestFile& testfile_in
                                     , std::string filePath)
    : _testfile(testfile_in)
      , _parser(std::make_unique<RapidAbstract>(filePath))
{
    _SetupEnums();
}
/*!
 * @brief Constructor, allows a different RapidAbstract implementation to be used
 * @param testfile_in The testfile object that represents the file we're reading in
 * @param parser_in A unique pointer containing the RapidAbstract implementation
 */
TestObjectBuilder::TestObjectBuilder(TestFile& testfile_in
                                     , std::unique_ptr<I_RapidAbstract> parser_in)
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
void TestObjectBuilder::TopLevelNode()
{
    const char* nodeName_str = nullptr;
    const char* temp = _parser->GetCurrentNodeName();

    /* If there's a child to move to */
    if (_parser->MoveToChild())
    {
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
                        throw analyserNodeInWrongPlace_Exception(nodeName_str
                                                                 , std::strlen(nodeName_str));
                }
            }
            else
            {
                throw analyserParserNullReturn_Exception("Top Level Node: ");
            }
        } while (_parser->MoveToNextNode());
    }
    else
    {
        throw analyserMalformedTestCase_Exception("No recognised children of <testcase>");
    }
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
                    newDP._dataPointString = _parser->GetNodeValue();
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
                        dp._operations.push_back(_handleOperation());
                        break;
                    case nodes_e::NODE_VARIABLE:
                        dp._variables.push_back(_handleVariable());
                        break;
                    default:
                        break;
                }
            }
            else
            {
                throw analyserParserNullReturn_Exception("Datapoint Node: ");
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
    /* testName, protocol, rate, etc*/
    if (_parser->GetCurrentNodeName())
    {
        do
        {
            int tagSucc = false;
            try
            {
                nodes_e nodeName = _nodeEnums.getValue(_parser->GetCurrentNodeName());
                switch (nodeName)
                {
                    case nodes_e::NODE_TESTNAME:
                        tagSucc = _ConfigTestName(conf) << 1;
                        break;
                    case nodes_e::NODE_PROTOCOL:
                        tagSucc = _ConfigProtocol(conf) << 2;
                        break;
                    case nodes_e::NODE_RATE:
                        tagSucc = _ConfigRate(conf) << 3;
                        break;
                    case nodes_e::NODE_CHAOS:
                        tagSucc = _ConfigChaos(conf) << 4;
                        break;
                    case nodes_e::NODE_DURATION:
                        tagSucc = _ConfigDuration(conf) << 5;
                        break;
                    case nodes_e::NODE_THREADS:
                        tagSucc = _ConfigThreads(conf) << 6;
                        break;
                    case nodes_e::NODE_THREADSPERINTERFACE:
                        tagSucc = _ConfigThreadsPerInterface(conf) << 7;
                        break;
                    default:
                        break;
                }
            }
            catch (baseAnalyser_Exception const& e)
            {
                // Log exception
            }
            //! @todo Check the tagSucc return
        } while (_parser->MoveToNextNode());
    }
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
    _nodeEnums.RegisterEnum("comms"
                            , nodes_e::NODE_COMMS);
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
    _attributeEnums.RegisterEnum("handler"
                                 , attributes_e::ATTR_HANDLER);
}
/*!
 * @brief Handles datapoint operation nodes
 * @return The new operation
 */
testOperation TestObjectBuilder::_handleOperation()
{
    testOperation newTO = {""};
    if (_parser->SelectAttribute())
    {
        do
        {
            const char* attrName_str = _parser->GetAttributeName();
            if (attrName_str)
            {
                attributes_e attrName = _attributeEnums.getValue(attrName_str);
                switch (attrName)
                {
                    case attributes_e::ATTR_NAME:
                        newTO._name = _parser->GetAttributeValue();
                        break;
                    case attributes_e::ATTR_STOREDIN:
                        newTO._storedIn = _parser->GetAttributeValue();
                        break;
                    case attributes_e::ATTR_VALUE:
                        newTO._value = _parser->GetAttributeValue();
                        break;
                    default:
                        break;
                }
            }
            else
            {
                throw analyserParserNullReturn_Exception("Operation Node: ");
            }
        } while (_parser->MoveToNextAttribute());
    }

    return newTO;
}
/*!
 * @brief Handles datapoint variable nodes
 * @return The new variable
 */
testVariable TestObjectBuilder::_handleVariable()
{
    testVariable newVar = {""};
    if (_parser->SelectAttribute())
    {
        do
        {
            const char* attrName_str = _parser->GetAttributeName();
            if (attrName_str)
            {
                attributes_e attrName = _attributeEnums.getValue(attrName_str);
                switch (attrName)
                {
                    case attributes_e::ATTR_NAME:
                        newVar._name = _parser->GetAttributeValue();
                        break;
                    case attributes_e::ATTR_ACTION:
                        newVar._action = _parser->GetAttributeValue();
                        break;
                    case attributes_e::ATTR_VALUE:
                        newVar._value = _parser->GetAttributeValue();
                        break;
                    default:
                        break;
                }
            }
            else
            {
                throw analyserParserNullReturn_Exception("Variable Node: ");
            }
        } while (_parser->MoveToNextAttribute());
    }

    return newVar;
}
/*!
 * @brief Sets the configuration objects testname field
 * @param TC A reference to the testconfiguration that we are editing
 * @return true for a successful read, otherwise false
 */
bool TestObjectBuilder::_ConfigTestName(testConfiguration& TC)
{
    bool retval = false;

    if (_parser->SelectAttribute())
    {
        attributes_e attrNAme =
            _attributeEnums.getValue(_parser->GetAttributeName());
        switch (attrNAme)
        {
            case attributes_e::ATTR_NAME:
                TC._testName = _parser->GetAttributeValue();
                retval = true;
                break;
            default:
                throw analyserWrongTagUsedInNode_Exception(_parser->GetAttributeName());
        }
    }

    return retval;
}
/*!
 * @brief Sets the configuration objects protocol field
 * @param TC A reference to the testconfiguration that we are editing
 * @return true for a successful read, otherwise false
 */
bool TestObjectBuilder::_ConfigProtocol(testConfiguration& TC)
{
    bool retval = false;

    if (_parser->SelectAttribute())
    {
        attributes_e attrNAme =
            _attributeEnums.getValue(_parser->GetAttributeName());
        switch (attrNAme)
        {
            case attributes_e::ATTR_PROTOCOL:
                TC._protocol = _parser->GetAttributeValue();
                retval = true;
                break;
            default:
                throw analyserWrongTagUsedInNode_Exception(_parser->GetAttributeName());
        }
    }

    return retval;
}
/*!
 * @brief Sets the configuration objects rate field
 * @param TC A reference to the testconfiguration that we are editing
 * @return true for a successful read, otherwise false
 */
bool TestObjectBuilder::_ConfigRate(testConfiguration& TC)
{
    bool retval = false;

    if (_parser->SelectAttribute())
    {
        attributes_e attrNAme =
            _attributeEnums.getValue(_parser->GetAttributeName());
        switch (attrNAme)
        {
            case attributes_e::ATTR_TPS:
                TC._tps = _parser->GetAttributeValue();
                retval = true;
                break;
            default:
                throw analyserWrongTagUsedInNode_Exception(_parser->GetAttributeName());
        }
    }

    return retval;
}
/*!
 * @brief Sets the configuration objects chaos mulitplier field
 * @param TC A reference to the testconfiguration that we are editing
 * @return true for a successful read, otherwise false
 */
bool TestObjectBuilder::_ConfigChaos(testConfiguration& TC)
{
    bool retval = false;

    if (_parser->SelectAttribute())
    {
        attributes_e attrNAme =
            _attributeEnums.getValue(_parser->GetAttributeName());
        switch (attrNAme)
        {
            case attributes_e::ATTR_MULTIPLIER:
                TC._chaosMulti = _parser->GetAttributeValue();
                retval = true;
                break;
            default:
                throw analyserWrongTagUsedInNode_Exception(_parser->GetAttributeName());
        }
    }

    return retval;
}
/*!
 * @brief Sets the configuration objects duration in seconds field
 * @param TC A reference to the testconfiguration that we are editing
 * @return true for a successful read, otherwise false
 */
bool TestObjectBuilder::_ConfigDuration(testConfiguration& TC)
{
    bool retval = false;

    if (_parser->SelectAttribute())
    {
        attributes_e attrNAme =
            _attributeEnums.getValue(_parser->GetAttributeName());
        switch (attrNAme)
        {
            case attributes_e::ATTR_SECONDS:
                TC._secondsDuration = _parser->GetAttributeValue();
                retval = true;
                break;
            default:
                throw analyserWrongTagUsedInNode_Exception(_parser->GetAttributeName());
        }
    }

    return retval;
}
/*!
 * @brief Sets the configuration objects max threads field
 * @param TC A reference to the testconfiguration that we are editing
 * @return true for a successful read, otherwise false
 */
bool TestObjectBuilder::_ConfigThreads(testConfiguration& TC)
{
    bool retval = false;

    if (_parser->SelectAttribute())
    {
        attributes_e attrNAme =
            _attributeEnums.getValue(_parser->GetAttributeName());
        switch (attrNAme)
        {
            case attributes_e::ATTR_MAXTHREADS:
                TC._maxThreads = _parser->GetAttributeValue();
                retval = true;
                break;
            default:
                throw analyserWrongTagUsedInNode_Exception(_parser->GetAttributeName());
        }
    }

    return retval;
}
/*!
 * @brief Sets the configuration objects threads per comms/interface field
 * @param TC A reference to the testconfiguration that we are editing
 * @return true for a successful read, otherwise false
 */
bool TestObjectBuilder::_ConfigThreadsPerInterface(testConfiguration& TC)
{
    bool retval = false;

    if (_parser->SelectAttribute())
    {
        attributes_e attrNAme =
            _attributeEnums.getValue(_parser->GetAttributeName());
        switch (attrNAme)
        {
            case attributes_e::ATTR_TPI:
                TC._threadsPerInter = _parser->GetAttributeValue();
                retval = true;
                break;
            default:
                throw analyserWrongTagUsedInNode_Exception(_parser->GetAttributeName());
        }
    }

    return retval;
}
/*!
 * @brief Sets the configuration objects comms interface we wish to use
 * @param TC A reference to the testconfiguration that we are editing
 * @return true for a successful read, otherwise false
 */
bool TestObjectBuilder::_ConfigCommsHandler(testConfiguration& TC)
{
    bool retval = false;

    if (_parser->SelectAttribute())
    {
        attributes_e attrNAme =
            _attributeEnums.getValue(_parser->GetAttributeName());
        switch (attrNAme)
        {
            case attributes_e::ATTR_HANDLER:
                TC._handler = _parser->GetAttributeValue();
                retval = true;
                break;
            default:
                throw analyserWrongTagUsedInNode_Exception(_parser->GetAttributeName());
        }
    }

    return retval;
}
} /* namespace testAnalyser2 */