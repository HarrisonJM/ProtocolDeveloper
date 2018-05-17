/*!
 * @brief defines all the mocks required to mock the C socket functions
 *
 * @addtogroup mocksLibrary
 *
 * @date May 2018
 *
 */

#include "gmock/gmock.h"
#include "interfaces/I_cNetComm.h"

namespace cFunctions
{

class cNetCommMocks : public I_cNetComm
{
public:
    cNetCommMocks() = default;
    MOCK_METHOD4(sendPacket, ssize_t(int sockfd, const void *buf, size_t len, int flags));
    MOCK_METHOD4(recvPacket, ssize_t(int sockfd, void *buf, size_t len, int flags));
    MOCK_METHOD1(closeConnection, int(int fd));
    MOCK_METHOD4(getAddrInfo, int(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res));
    MOCK_METHOD1(freeAddrInfo, void(struct addrinfo *res));
    MOCK_METHOD3(createSocket, int(int domain, int type, int protocol));
    MOCK_METHOD3(connectToRemote, int(int sockfd, const struct sockaddr *addr, socklen_t addrlen));

};

} /* namespace cFunctions */