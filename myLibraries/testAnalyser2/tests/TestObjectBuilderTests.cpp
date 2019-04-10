/*!
 * @brief TestObjectBuilder tests
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
#include "../src/testObjectBuilder.h"

namespace testAnalyser2
{
class TesTObjectBuilderFixture
    : public ::testing::Test
{
protected:
    TestFile testfile_in;
    TestObjectBuilder* tob;

    void SetUp()
    {
        tob = new TestObjectBuilder(testfile_in
                                    , "/home/hmarcks/src/ProtocolDeveloper/myLibraries/testAnalyser2/tests/test.xml");
    }

    void TearDown()
    {
        delete tob;
    }
};

TEST_F(TesTObjectBuilderFixture
       , Constructor)
{
    TestFile newTF;
    TestObjectBuilder tob2(newTF
                           , "/home/hmarcks/src/ProtocolDeveloper/myLibraries/testAnalyser2/tests/test.xml");
    // At least it didn't throw!
}

TEST_F(TesTObjectBuilderFixture
       , BuildTestObject)
{
    tob->TopLevelNode();

    ASSERT_EQ(1
              , testfile_in.GetNumberOfDataPoints());
    auto DP = testfile_in.GetAllDataPoints();

    ASSERT_EQ(std::string(DP[0]._dataPointString)
              , std::string("[TEST]"));
    ASSERT_EQ(std::string(DP[0]._variables[0]._name)
              , std::string("TEST"));
    ASSERT_EQ(std::string(DP[0]._variables[0]._action)
              , std::string("Swap"));
    ASSERT_EQ(std::string(DP[0]._variables[0]._value)
              , std::string("BOOP"));
    ASSERT_EQ(std::string(DP[0]._operations[0]._name)
              , std::string("OperationTest"));
    ASSERT_EQ(std::string(DP[0]._operations[0]._storedIn)
              , std::string("TEST"));
    ASSERT_EQ(std::string(DP[0]._operations[0]._value)
              , std::string("BOOP"));

    ASSERT_EQ(std::string(testfile_in.GetTestConfiguration()._testName)
              , std::string("testtest"));
    ASSERT_EQ(std::string(testfile_in.GetTestConfiguration()._protocol)
              , std::string("testProt"));
    ASSERT_EQ(std::string(testfile_in.GetTestConfiguration()._tps)
              , std::string("57"));
    ASSERT_EQ(std::string(testfile_in.GetTestConfiguration()._chaosMulti)
              , std::string("0XDEADBEEF"));
    ASSERT_EQ(std::string(testfile_in.GetTestConfiguration()._secondsDuration)
              , std::string("1010101"));
    ASSERT_EQ(std::string(testfile_in.GetTestConfiguration()._maxThreads)
              , std::string("99"));
    ASSERT_EQ(std::string(testfile_in.GetTestConfiguration()._threadsPerInter)
              , std::string("0"));
    ASSERT_EQ(std::string(testfile_in.GetTestConfiguration()._commsHandler)
              , std::string("testComms"));
}

TEST_F(TesTObjectBuilderFixture
       , CheckExceptions)
{
    // TODO
}

} /* namespace testAnalyser2 */