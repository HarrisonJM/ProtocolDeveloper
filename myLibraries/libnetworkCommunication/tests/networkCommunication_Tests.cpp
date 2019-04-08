/*!
 * @brief
 */

#include <libnetworkCommunication/libNetworkCommunication.h>
#include "mockLibrary/cNetCommMocks.h"

using ::testing::StrictMock;
using ::testing::Return;
using ::testing::_;
using ::testing::MatchesRegex;
using ::testing::SetArgPointee;

namespace Communication
{

class networkCommunicationTests
    : public ::testing::Test
{
protected:

    std::shared_ptr<libNetworkCommunication::libNetworkCommunication> nC;
    std::shared_ptr<StrictMock<cFunctions::cNetCommMocks>> cnetmock;
    addrinfo* testData;

    void SetUp() override
    {
        nC->_alreadyConnected = false;
        cnetmock = std::make_shared<StrictMock<cFunctions::cNetCommMocks>>();
        nC = std::make_shared<libNetworkCommunication::libNetworkCommunication>(cnetmock);
    }

    void TearDown() override
    {
        nC->_alreadyConnected = false;
        freeaddrinfo(testData);
    }

    //! @todo this
    void setupServinfo(addrinfo** testData)
    {
        addrinfo hints = {0};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // Do *my* IP for me
        getaddrinfo("localhost"
                    , "9687"
                    , &hints
                    , testData);
    }

    void setupGetAddrInfo_Success()
    {
        nC->_alreadyConnected = false;
        setupServinfo(&testData);
        freeaddrinfo(testData->ai_next);
        testData->ai_next = nullptr;
        EXPECT_CALL(*cnetmock
                    , getaddressinfo(MatchesRegex("127.0.0.1")
                                     , MatchesRegex("9687")
                                     , _
                                     , _))
            .Times(1)
            .WillOnce(DoAll(SetArgPointee<3>(testData)
                            , Return(0)));
    }
};

TEST_F(networkCommunicationTests
       , SendData)
{
    EXPECT_CALL(*cnetmock
                , sendTo(-1
                         , nullptr
                         , 0
                         , 16384))
        .Times(2)
        .WillOnce(Return(1))
        .WillOnce(Return(-1));

    EXPECT_EQ(nC->SendData(nullptr
                           , 0)
              , 1);

    testing::internal::CaptureStderr();
    ASSERT_EQ(nC->SendData(nullptr
                           , 0)
              , -1);
    ASSERT_EQ(testing::internal::GetCapturedStderr()
              , "Send: Success\n");
}

TEST_F(networkCommunicationTests
       , ReceiveData)
{
    EXPECT_CALL(*cnetmock
                , recvFrom(-1
                           , NULL
                           , 0
                           , 0))
        .Times(2)
        .WillOnce(Return(1))
        .WillOnce(Return(-1));
    EXPECT_EQ(nC->ReceiveData(nullptr
                              , 0)
              , 1);

    testing::internal::CaptureStderr();
    ASSERT_EQ(nC->ReceiveData(nullptr
                              , 0)
              , -1);
    ASSERT_EQ(testing::internal::GetCapturedStderr()
              , "Recv: Success\n");
}

TEST_F(networkCommunicationTests
       , EstablishConnection_Success)
{
    setupGetAddrInfo_Success();

    EXPECT_CALL(*cnetmock
                , createSocket(testData->ai_family
                               , testData->ai_socktype
                               , testData->ai_protocol))
        .Times(1)
        .WillOnce(Return(99));

    EXPECT_CALL(*cnetmock
                , connectToRemote(99
                                  , testData->ai_addr
                                  , testData->ai_addrlen))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*cnetmock
                , freeaddressinfo(_))
        .Times(1);

    ASSERT_TRUE(nC->EstablishConnection());
    nC->_alreadyConnected = false;
}

TEST_F(networkCommunicationTests
       , EstablishConnection_getAddr_Fail)
{
    EXPECT_CALL(*cnetmock
                , getaddressinfo(MatchesRegex("127.0.0.1")
                                 , MatchesRegex("9687")
                                 , _
                                 , _))
        .Times(1)
        .WillOnce(Return(-1));

    testing::internal::CaptureStderr();
    ASSERT_FALSE(nC->EstablishConnection());
    nC->_alreadyConnected = false;
    std::string stderrOut = testing::internal::GetCapturedStderr();

    ASSERT_EQ(stderrOut
              , "getaddr failure in SetupAddrInfo(): Bad value for ai_flags");
}

TEST_F(networkCommunicationTests
       , EstablishConnection_socket_Fail)
{
    setupGetAddrInfo_Success();

    EXPECT_CALL(*cnetmock
                , createSocket(testData->ai_family
                               , testData->ai_socktype
                               , testData->ai_protocol))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_CALL(*cnetmock
                , freeaddressinfo(_))
        .Times(1);

    testing::internal::CaptureStderr();
    ASSERT_FALSE(nC->EstablishConnection());
    nC->_alreadyConnected = false;
    ASSERT_EQ(testing::internal::GetCapturedStderr()
              , "client socket: No such file or directory\nCould not connect to remote\n");
}

TEST_F(networkCommunicationTests
       , EstablishConnection_connect_Fail)
{
    setupGetAddrInfo_Success();

    EXPECT_CALL(*cnetmock
                , createSocket(testData->ai_family
                               , testData->ai_socktype
                               , testData->ai_protocol))
        .Times(1)
        .WillOnce(Return(99));

    EXPECT_CALL(*cnetmock
                , connectToRemote(99
                                  , testData->ai_addr
                                  , testData->ai_addrlen))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_CALL(*cnetmock
                , closeConnection(99))
        .Times(1);

    EXPECT_CALL(*cnetmock
                , freeaddressinfo(_))
        .Times(1);

    testing::internal::CaptureStderr();
    ASSERT_FALSE(nC->EstablishConnection());
    nC->_alreadyConnected = false;
    ASSERT_EQ(testing::internal::GetCapturedStderr()
              , "client connect: No such file or directory\nCould not connect to remote\n");
}

int main(int argc
         , char** argv)
{
    ::testing::InitGoogleTest(&argc
                              , argv);
    return RUN_ALL_TESTS();
}
}