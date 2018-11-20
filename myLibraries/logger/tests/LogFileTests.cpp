/*!
 * @brief Tests related to the logFile class
 */

#include "../src/LogFile.h"
#include "gtest/gtest.h"

namespace LoggerClasses {

class LogFileTests : public ::testing::Test
{
protected:

    LogFile *_testLogBasic;
    std::stringstream* _logFileOut;
    std::unique_ptr<std::stringstream> _ss;
    // This variable will be used to gradually track the log as a test is conducted
    std::string _runningLogFile;
    std::string _lastLogMessage;
    std::condition_variable _testCondVar;
    void SetUp() override
    {
        _ss = std::make_unique<std::stringstream>();
        _logFileOut = _ss.get();
        _testLogBasic = new LogFile("testLogBasic",
                                   "",
                                   std::move(_ss),
                                   _testCondVar);
        _runningLogFile =
            "************************************************************\n\
Log file:          testLogBasic\n\
Date:              DATE REPLACE\n\
Extra Information: \n\
************************************************************\n\
********************* LOG STARTS BELOW *********************\n\
************************************************************\n\
\n";
    }

    void addMessageToLog(std::string messageToAdd,
                         logLevel lvl)
    {
        _testLogBasic->AddLogMessage(messageToAdd,
                                    lvl);
        _lastLogMessage = _testLogBasic->ReturnLatestMessage();

        _runningLogFile += _lastLogMessage;
    }

    void TearDown()
    {
//        std::cout << "teardown" << std::endl;
    }
};

TEST_F(LogFileTests,
       Constructor)
{
    ASSERT_EQ(_testLogBasic->ReturnOldestMessage(),
              _runningLogFile);
}

TEST_F(LogFileTests,
       outStreamHeader)
{
    _testLogBasic->WriteAllMessagesToStream();
    EXPECT_EQ(_logFileOut->str(),
              _runningLogFile);
}

TEST_F(LogFileTests,
       addMessages)
{
    addMessageToLog("TESTMESSAGE",
                    logLevel::INFO);
    _testLogBasic->WriteAllMessagesToStream();
    EXPECT_EQ(_runningLogFile,
              _logFileOut->str());
}

TEST_F(LogFileTests,
       checkHeadTailReturns)
{
    //! Write the header to the stream
    _testLogBasic->WriteAllMessagesToStream();
    ASSERT_EQ(_logFileOut->str(),
              _runningLogFile);

    _testLogBasic->AddLogMessage("CHECKINGHEAD",
                                logLevel::INFO);
    ASSERT_EQ(std::string("[INFO][Date]: CHECKINGHEAD\n"),
              _testLogBasic->ReturnOldestMessage());

    _testLogBasic->AddLogMessage("CHECKINGTAIL",
                                logLevel::INFO);
    ASSERT_EQ(std::string("[INFO][Date]: CHECKINGTAIL\n"),
              _testLogBasic->ReturnLatestMessage());
    //double check head
    ASSERT_EQ(std::string("[INFO][Date]: CHECKINGHEAD\n"),
              _testLogBasic->ReturnOldestMessage());

    _testLogBasic->AddLogMessage("CHECKINGTAIL2",
                                logLevel::INFO);
    ASSERT_EQ(std::string("[INFO][Date]: CHECKINGTAIL2\n"),
              _testLogBasic->ReturnLatestMessage());
    //triple check head
    ASSERT_EQ(std::string("[INFO][Date]: CHECKINGHEAD\n"),
              _testLogBasic->ReturnOldestMessage());
}

TEST_F(LogFileTests,
       checkLogLevels)
{
    //! Write the header to the stream
    _testLogBasic->WriteAllMessagesToStream();
    ASSERT_EQ(_logFileOut->str(),
              _runningLogFile);

    _testLogBasic->AddLogMessage("CHECKINGINFO",
                                logLevel::INFO);
    ASSERT_EQ(std::string("[INFO][Date]: CHECKINGINFO\n"),
              _testLogBasic->ReturnOldestMessage());

    _testLogBasic->AddLogMessage("CHECKINGWARNING",
                                logLevel::WARNING);
    ASSERT_EQ(std::string("[WARNING][Date]: CHECKINGWARNING\n"),
              _testLogBasic->ReturnLatestMessage());

    _testLogBasic->AddLogMessage("CHECKINGERROR",
                                logLevel::ERROR);
    ASSERT_EQ(std::string("[ERROR][Date]: CHECKINGERROR\n"),
              _testLogBasic->ReturnLatestMessage());

    _testLogBasic->AddLogMessage("CHECKINGDEBUG",
                                logLevel::DEBUG);
    ASSERT_EQ(std::string("[DEBUG][Date]: CHECKINGDEBUG\n"),
              _testLogBasic->ReturnLatestMessage());
}

TEST_F(LogFileTests,
       multiplemessagesonQueue)
{
    addMessageToLog("message 1",
                    logLevel::DEBUG);
    addMessageToLog("message 2",
                    logLevel::DEBUG);
    addMessageToLog("message 3",
                    logLevel::DEBUG);
    _testLogBasic->WriteAllMessagesToStream();

    ASSERT_EQ(_runningLogFile,
              _logFileOut->str());
}

TEST_F(LogFileTests,
       ExtraInformationString)
{
    std::unique_ptr<std::stringstream> EISOut;
    std::condition_variable condvar;
    std::string csvout = "************************************************************\n"
                         "Log file:          EIS\n"
                         "Date:              DATE REPLACE\n"
                         "Extra Information: Just\n"
                         "               some\n"
                         "               csv\n"
                         "               values\n"
                         "               \n"
                         "************************************************************\n"
                         "********************* LOG STARTS BELOW *********************\n"
                         "************************************************************\n\n";
    LogFile *testLogEIS = new LogFile("EIS",
                                      "Just,some,csv,values",
                                      std::move(EISOut),
                                      condvar);

    ASSERT_EQ(testLogEIS->ReturnLatestMessage(), csvout);
}

int main(int argc,
         char **argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}

}