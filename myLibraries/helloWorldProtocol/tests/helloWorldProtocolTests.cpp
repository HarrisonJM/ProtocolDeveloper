/*!
 * @brief Unit tests for the helloworld protocol
 *
 * @date 19/02/2019
 *
 * @author hmarcks
 * @addtogroup helloWorldProtocol
 * @{
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <I_protocolInterface.h>
#include <HelloWorldProtocol.h>

namespace helloWorldProtocol
{

static const char* helloStr = "Hello, World!\r\n\0\0\0";
static const char* goodbyeStr = "Goodbye, World!\r\n\0\0\0";
static const char* errorStr = "ERROR\r\n";

/* The google test strategy */
class helloworldPStrategy
    : public ::testing::Test
{
protected:
    /* Returns a basic datapoint for testing with */
    class testDPBuilder
    {
    public:
        explicit testDPBuilder(int action)
            : _action(action)
        {
        }

        void getTestDP(testAnalyser2::dataPoint& testDP)
        {
            testAnalyser2::testVariable testVar;
            testAnalyser2::testOperation testOp;

            testVar._action = "test action";
            testVar._name = "test name";

            switch (_action)
            {
                case 0:
                    testVar._value = helloStr;
                    break;
                case 1:
                    testVar._value = goodbyeStr;
                    break;
                case 2:
                default:
                    testVar._value = errorStr;
                    break;
            }

            testOp._storedIn = "test storedIn";
            testOp._name = "test name";
            testOp._value = "test value";

            testDP._variables.push_back(testVar);
            testDP._operations.push_back(testOp);
            testDP._dataPointString = "[hellogoodbye]";
        }
    private:
        int _action;
    };

    /* Returns a datstruct for testing with */
    class testDSBuilder
    {
    public:
        explicit testDSBuilder(int action)
            : _action(action)
        {}

        ~testDSBuilder()
        {
            delete ds;
        }

        Protocol::DataStruct* getDatastruct()
        {
            ds = new Protocol::DataStruct;
            ds->_size = 20;

            switch (_action)
            {
                case 0:
                    ds->_data_p = (void*) helloStr;
                    break;
                case 1:
                    ds->_data_p = (void*) goodbyeStr;
                    break;
                case 2:
                default:
                    ds->_data_p = (void*) errorStr;
                    break;
            }

            return ds;
        }

    private:
        int _action;
        Protocol::DataStruct* ds;
        char* dataPacket;
    };

    std::shared_ptr<Protocol::DataStruct> Data;
    Protocol::I_protocolInterface* protocol;

    void SetUp() override
    {
        protocol = new HelloWorldProtocol;
    }

    void TearDown() override
    {
        delete protocol;
    }
    testAnalyser2::dataPoint getDP(int action)
    {
        testAnalyser2::dataPoint dp1;
        switch (action)
        {
            case 0:
                _getTestDP_Hello(dp1);
                break;
            case 1:
                _getTestDP_Goodbye(dp1);
                break;
            case 3:
                _getTestDP_Error(dp1);
                break;
            default:
                _getTestDP_Error(dp1);
                break;
        }

        return std::move(dp1);
    }

private:
    void _getTestDP_Hello(testAnalyser2::dataPoint testDP)
    {
        testDPBuilder testDPBuilder1(0);
        testDPBuilder1.getTestDP(testDP);
    }
    void _getTestDP_Goodbye(testAnalyser2::dataPoint testDP)
    {
        testDPBuilder testDPBuilder1(1);
        testDPBuilder1.getTestDP(testDP);
    }
    void _getTestDP_Error(testAnalyser2::dataPoint testDP)
    {
        testDPBuilder testDPBuilder1(2);
        testDPBuilder1.getTestDP(testDP);
    }
};

TEST_F(helloworldPStrategy
       , Constructor)
{
    HelloWorldProtocol hw;
    testAnalyser2::dataPoint dp1;
    dp1 = getDP(0);
    hw.SetDataPoints(dp1);
}

TEST_F(helloworldPStrategy
       , DecodeResult)
{
    testAnalyser2::dataPoint dp1;
    dp1 = getDP(0);
    protocol->SetDataPoints(dp1);
    // Success
    {
        testDSBuilder testDSBuilder0(0);
        ASSERT_EQ(helloStr
                  , testDSBuilder0.getDatastruct()->_data_p);
        protocol->DecodeResult(std::make_shared<Protocol::DataStruct>(*testDSBuilder0.getDatastruct()));
        ASSERT_EQ(protocol->GetResultCode()
                  , 0);
        testDSBuilder testDSBuilder1(1);
        ASSERT_EQ(goodbyeStr
                  , testDSBuilder1.getDatastruct()->_data_p);
        protocol->DecodeResult(std::make_shared<Protocol::DataStruct>(*testDSBuilder1.getDatastruct()));
        ASSERT_EQ(protocol->GetResultCode()
                  , 0);
    }
    // Error
    {
        testDSBuilder testDSBuilder2(2);
        protocol->DecodeResult(std::make_shared<Protocol::DataStruct>(*testDSBuilder2.getDatastruct()));
        ASSERT_EQ(protocol->GetResultCode()
                  , 1);
    }
}

TEST_F(helloworldPStrategy
       , GetDataToSend)
{
    testAnalyser2::dataPoint dp1;
    dp1 = getDP(0);
    protocol->SetDataPoints(dp1);

    testDSBuilder testDSBuilder0(0);
    protocol->DecodeResult(std::make_shared<Protocol::DataStruct>(*testDSBuilder0.getDatastruct()));
    auto data = protocol->GetDataToSend();
    ASSERT_EQ((char*) data->_data_p
              , std::string(goodbyeStr));

    testDSBuilder testDSBuilder1(1);
    protocol->DecodeResult(std::make_shared<Protocol::DataStruct>(*testDSBuilder1.getDatastruct()));
    auto data2 = protocol->GetDataToSend();
    ASSERT_EQ((char*) data2->_data_p
              , std::string(helloStr));

    testDSBuilder testDSBuilder2(2);
    protocol->DecodeResult(std::make_shared<Protocol::DataStruct>(*testDSBuilder2.getDatastruct()));
    auto data3 = protocol->GetDataToSend();
    ASSERT_EQ((char*) data2->_data_p
              , std::string(helloStr));
}

TEST_F(helloworldPStrategy
       , GetResult)
{
    testAnalyser2::dataPoint dp1;
    dp1 = getDP(0);
    protocol->SetDataPoints(dp1);

    testDSBuilder testDSBuilder0(0);
    protocol->DecodeResult(std::make_shared<Protocol::DataStruct>(*testDSBuilder0.getDatastruct()));
    auto data = protocol->GetResult();
    ASSERT_EQ((char*) data->_data_p
              , std::string(helloStr));
}
} /* namespace helloWorldProtocol */

/*! @} */