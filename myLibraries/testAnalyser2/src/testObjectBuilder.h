/*!
 * @brief Builds the actual testfile object for use by the test threads
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 03/01/19
 *
 * @todo rapidabstract interface
 */

#ifndef PROTOCOLDEVELOPER_TESTOBJECTBUILDER_H
#define PROTOCOLDEVELOPER_TESTOBJECTBUILDER_H

#include <testAnalyser2/testFile.h>
#include <utility/enumHandler.h>
#include "rapidAbstract.h"

namespace testAnalyser2
{

enum nodes_e
    : short
{
    NODE_NULL,
    NODE_DATAPOINT,
    NODE_CONFIG,
    NODE_VARIABLE,
    NODE_OPERATION,
    NODE_PROTOCOL,
    NODE_RATE,
    NODE_CHAOS,
    NODE_DURATION,
    NODE_THREADS,
    NODE_TESTNAME,
    NODE_THREADSPERINTERFACE,
    NODE_COMMS
};

enum attributes_e
    : short
{
    ATTR_NULL,
    ATTR_PROTOCOL,
    ATTR_TPS,
    ATTR_MULTIPLIER,
    ATTR_SECONDS,
    ATTR_MAXTHREADS,
    ATTR_NAME,
    ATTR_ACTION,
    ATTR_VALUE,
    ATTR_STOREDIN,
    ATTR_TPI,
    ATTR_HANDLER
};

class TestObjectBuilder
{
public:
    TestObjectBuilder(TestFile& testfile_in
                      , std::string filePath);
    TestObjectBuilder(TestFile& testfile_in
                      , std::unique_ptr<I_RapidAbstract> parser_in);
    ~TestObjectBuilder() = default;

    /*!
     * @brief Where we enter the testcase
     */
    void TopLevelNode();

private:
    TestFile& _testfile;
    std::unique_ptr<I_RapidAbstract> _parser;
    utility::EnumHandler<std::string, nodes_e> _nodeEnums;
    utility::EnumHandler<std::string, attributes_e> _attributeEnums;

    /*!
     * @brief Setsup all the enums we'll be using and they're string equivalents
     */
    void _SetupEnums();
    /*!
     * @brief The datapoint node
     */
    void _DataPointNode();
    /*!
     * @brief Children of the data point node
     * @param dp A reference to the datapoint we're editing
     */
    void _DataPointChild(dataPoint& dp);
    /*!
     * @brief The configuration node
     */
    void _ConfigurationNode();
    /*!
     * @brief Children of the configuration node
     * @param conf A reference to the configuration we're editing
     */
    void _ConfigurationChild(testConfiguration& conf);
    /*!
     * @brief Sets up the strings->enums for the nodes
     */
    void _SetupNodeEnums();
    /*!
     * @brief Sets up the strings->enums for the attributes
     */
    void _SetupAttrEnums();
    /*!
     * @brief Handles datapoint operation nodes
     * @return The new operation
     */
    testOperation _handleOperation();
    /*!
     * @brief Handles datapoint variable nodes
     * @return The new variable
     */
    testVariable _handleVariable();

    bool _ConfigTestName(testConfiguration& TC);
    bool _ConfigProtocol(testConfiguration& TC);
    bool _ConfigRate(testConfiguration& TC);
    bool _ConfigChaos(testConfiguration& TC);
    bool _ConfigDuration(testConfiguration& TC);
    bool _ConfigThreads(testConfiguration& TC);
    bool _ConfigThreadsPerInterface(testConfiguration& TC);
    bool _ConfigCommsHandler(testConfiguration& TC);
};
} /* namespace testAnalyser2 */

#endif /* PROTOCOLDEVELOPER_TESTOBJECTBUILDER_H */
