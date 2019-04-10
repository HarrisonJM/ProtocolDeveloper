/*!
 * @brief tests for the rapidabstract abstraction
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 * @{
 * @addtogroup tests
 * @{
 * @date 12/01/19
 */

#include <gtest/gtest.h>
#include <../src/rapidAbstract.h>

namespace testAnalyser2
{

class RapidAbstractFixture
    : public ::testing::Test
{
protected:
    RapidAbstract* extractor;

    void SetUp()
    {
        extractor = new RapidAbstract("/home/hmarcks/src/ProtocolDeveloper/myLibraries/testAnalyser2/tests/test.xml");
    }

    void TearDown()
    {
        delete extractor;
    }

    void CheckConfigNodes(std::string nodeName
                          , std::string attributeName
                          , std::string attributeValue)
    {
        EXPECT_EQ(nodeName
                  , std::string(extractor->GetCurrentNodeName()));
        EXPECT_TRUE(extractor->SelectAttribute());
        EXPECT_EQ(attributeName
                  , std::string(extractor->GetAttributeName()));
        EXPECT_EQ(attributeValue
                  , std::string(extractor->GetAttributeValue()));
    }
};

TEST_F(RapidAbstractFixture
       , Constructor)
{
    ASSERT_EQ(std::string("testCase")
              , std::string(extractor->GetCurrentNodeName()));

    ASSERT_EQ(extractor->GetCurrentNodeType()
              , rapidxml::node_type::node_element);
}

/*
<dataPoint>
    [TEST]
    <variable name="TEST" action="Swap" value="BOOP"/>
    <operation name="OperationTest" storedIn="TEST" value="BOOP"/>
</dataPoint>
 */
TEST_F(RapidAbstractFixture
       , CompleteDataPoint)
{
    EXPECT_EQ(std::string("testCase")
              , std::string(extractor->GetCurrentNodeName()));
    EXPECT_TRUE(extractor->MoveToChild());
    EXPECT_EQ(std::string("dataPoint")
              , std::string(extractor->GetCurrentNodeName()));

    EXPECT_TRUE(extractor->SelectAttribute());
    EXPECT_EQ(std::string(extractor->GetAttributeValue())
              , std::string("[TEST]"));
    EXPECT_TRUE(extractor->MoveToChild());

    EXPECT_EQ(std::string("variable")
              , std::string(extractor->GetCurrentNodeName()));
    EXPECT_TRUE(extractor->SelectAttribute());
    EXPECT_EQ(std::string(extractor->GetAttributeValue())
              , std::string("TEST"));
    EXPECT_TRUE(extractor->MoveToNextAttribute());
    EXPECT_EQ(std::string(extractor->GetAttributeValue())
              , std::string("Swap"));
    EXPECT_TRUE(extractor->MoveToNextAttribute());
    EXPECT_EQ(std::string(extractor->GetAttributeValue())
              , std::string("BOOP"));
    EXPECT_TRUE(extractor->MoveToNextNode());

    EXPECT_EQ(std::string("operation")
              , std::string(extractor->GetCurrentNodeName()));
    EXPECT_TRUE(extractor->SelectAttribute());
    EXPECT_EQ(std::string(extractor->GetAttributeValue())
              , std::string("OperationTest"));
    EXPECT_TRUE(extractor->MoveToNextAttribute());
    EXPECT_EQ(std::string(extractor->GetAttributeValue())
              , std::string("TEST"));
    EXPECT_TRUE(extractor->MoveToNextAttribute());
    EXPECT_EQ(std::string(extractor->GetAttributeValue())
              , std::string("BOOP"));

    extractor->ExitChild();
}

TEST_F(RapidAbstractFixture
       , CompleteConfiguration)
{
    EXPECT_EQ(std::string("testCase")
              , std::string(extractor->GetCurrentNodeName()));
    EXPECT_TRUE(extractor->MoveToChild());
    EXPECT_EQ(std::string("dataPoint")
              , std::string(extractor->GetCurrentNodeName()));
    EXPECT_TRUE(extractor->MoveToNextNode());
    EXPECT_EQ(std::string("config")
              , std::string(extractor->GetCurrentNodeName()));
    EXPECT_TRUE(extractor->MoveToChild());
    CheckConfigNodes("testName"
                     , "name"
                     , "testtest");
    EXPECT_TRUE(extractor->MoveToNextNode());
    CheckConfigNodes("protocol"
                     , "protocol"
                     , "testProt");
    EXPECT_TRUE(extractor->MoveToNextNode());
    CheckConfigNodes("rate"
                     , "tps"
                     , "57");
    EXPECT_TRUE(extractor->MoveToNextNode());
    CheckConfigNodes("chaos"
                     , "multiplier"
                     , "0XDEADBEEF");
    EXPECT_TRUE(extractor->MoveToNextNode());
    CheckConfigNodes("duration"
                     , "seconds"
                     , "1010101");
    EXPECT_TRUE(extractor->MoveToNextNode());
    CheckConfigNodes("threads"
                     , "max"
                     , "99");
    EXPECT_TRUE(extractor->MoveToNextNode());
    CheckConfigNodes("threadsPerInterface"
                     , "tpi"
                     , "0");
    EXPECT_TRUE(extractor->MoveToNextNode());
    CheckConfigNodes("comms"
                     , "handler"
                     , "testComms");
    extractor->ExitChild();
    extractor->ExitChild();
}
} /* namespace testAnalyser2 */