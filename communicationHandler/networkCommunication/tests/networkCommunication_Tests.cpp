/*!
 * @brief
 */

#include "../NetworkCommunication.h"
#include "mockLibrary/cNetCommMocks.h"
#include "mockLibrary/cStdLibMocks.h"

#include <netdb.h>

using ::testing::StrictMock;
using ::testing::Return;
using ::testing::_;
using ::testing::MatchesRegex;
using ::testing::SetArgPointee;

namespace Communication
{

class networkCommunicationTests: public ::testing::Test
{
protected:

    NetworkCommunication* nC;
    StrictMock<cFunctions::cNetCommMocks> *cnetmock;
    addrinfo* testData;

    void SetUp() override
    {
        nC = new NetworkCommunication;
        cnetmock = new StrictMock<cFunctions::cNetCommMocks>;
        nC->setInterface(cnetmock);
    }

    void TearDown() override
    {
        freeaddrinfo(testData);
        delete(nC);
    }

    //! @todo this
    void setupServinfo(addrinfo **testData)
    {
        addrinfo hints = {0};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // Do *my* IP for me
        getaddrinfo("localhost", "9687", &hints, testData);
    }

    void setupGetAddrInfo_Success()
    {
        setupServinfo(&testData);
        freeaddrinfo(testData->ai_next);
        testData->ai_next = NULL;
        EXPECT_CALL(*cnetmock, getAddrInfo(MatchesRegex("localhost"),
                                           MatchesRegex("9687"),
                                           _,
                                           _))
            .Times(1)
            .WillOnce(DoAll(SetArgPointee<3>(testData), Return(0)));
    }

};

TEST_F(networkCommunicationTests,
       SendData)
{
    EXPECT_CALL(*cnetmock, sendPacket(-1, NULL, 0, 0))
        .Times(2)
        .WillOnce(Return(1))
        .WillOnce(Return(-1));

    EXPECT_EQ(nC->SendData(nullptr, 0), 1);

    testing::internal::CaptureStderr();
    ASSERT_EQ(nC->SendData(nullptr, 0), -1);
    ASSERT_EQ(testing::internal::GetCapturedStderr(), "Send: Inappropriate ioctl for device\n");
}

TEST_F(networkCommunicationTests,
       ReceiveData)
{
    EXPECT_CALL(*cnetmock, recvPacket(-1, NULL, 0, 0))
        .Times(2)
        .WillOnce(Return(1))
        .WillOnce(Return(-1));
    EXPECT_EQ(nC->ReceiveData(nullptr, 0), 1);

    testing::internal::CaptureStderr();
    ASSERT_EQ(nC->ReceiveData(nullptr, 0), -1);
    ASSERT_EQ(testing::internal::GetCapturedStderr(), "Recv: Inappropriate ioctl for device\n");
}

TEST_F(networkCommunicationTests,
       EstablishConnection_Success)
{
    setupGetAddrInfo_Success();

    EXPECT_CALL(*cnetmock, createSocket(testData->ai_family,
                                        testData->ai_socktype,
                                        testData->ai_protocol))
        .Times(1)
        .WillOnce(Return(99));

    EXPECT_CALL(*cnetmock, connectToRemote(99,
                                           testData->ai_addr,
                                           testData->ai_addrlen))
        .Times(1)
        .WillOnce(Return(0));

    EXPECT_CALL(*cnetmock, freeAddrInfo(_))
        .Times(1);

    ASSERT_TRUE(nC->EstablishConnection());
}

TEST_F(networkCommunicationTests,
       EstablishConnection_getAddr_Fail)
{
    EXPECT_CALL(*cnetmock, getAddrInfo(MatchesRegex("localhost"),
                                       MatchesRegex("9687"),
                                       _,
                                       _))
        .Times(1)
        .WillOnce(Return(-1));

    testing::internal::CaptureStderr();
    ASSERT_FALSE(nC->EstablishConnection());
    std::string stderrOut = testing::internal::GetCapturedStderr();

    ASSERT_EQ(stderrOut,
              "getaddr failure in SetupAddrInfo(): Bad value for ai_flags");
}

TEST_F(networkCommunicationTests,
       EstablishConnection_socket_Fail)
{
    setupGetAddrInfo_Success();

    EXPECT_CALL(*cnetmock, createSocket(testData->ai_family,
                                        testData->ai_socktype,
                                        testData->ai_protocol))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_CALL(*cnetmock, freeAddrInfo(_))
        .Times(1);

    testing::internal::CaptureStderr();
    ASSERT_FALSE(nC->EstablishConnection());
    ASSERT_EQ(testing::internal::GetCapturedStderr(),
"client socket: No such file or directory\nCould not connect to remote\n");
}

TEST_F(networkCommunicationTests,
       EstablishConnection_connect_Fail)
{
    setupGetAddrInfo_Success();

    EXPECT_CALL(*cnetmock, createSocket(testData->ai_family,
                                        testData->ai_socktype,
                                        testData->ai_protocol))
        .Times(1)
        .WillOnce(Return(99));

    EXPECT_CALL(*cnetmock, connectToRemote(99,
                                           testData->ai_addr,
                                           testData->ai_addrlen))
        .Times(1)
        .WillOnce(Return(-1));

    EXPECT_CALL(*cnetmock, closeConnection(99))
        .Times(1);

    EXPECT_CALL(*cnetmock, freeAddrInfo(_))
        .Times(1);

    testing::internal::CaptureStderr();
    ASSERT_FALSE(nC->EstablishConnection());
    ASSERT_EQ(testing::internal::GetCapturedStderr(),
    "client connect: No such file or directory\nCould not connect to remote\n");
}

int main(int argc,
         char **argv)
{
    ::testing::InitGoogleTest(&argc,
                              argv);
    return RUN_ALL_TESTS();
}

}