/*!
 * @brief Wrapper class to allow mocking the network communication libraries
 * provided from C
 *
 * @addtogroup cMocking
 *
 * @date 09/05/2018
 */

#ifndef PROTOCOLDEVELOPER_CNETCOMM_H
#define PROTOCOLDEVELOPER_CNETCOMM_H

#include "interfaces/I_cNetComm.h"

namespace cFunctions
{

class cNetComm : public I_cNetComm
{

public:
    cNetComm() = default;
    ~cNetComm() = default;

    virtual ssize_t sendPacket(int sockfd,
                       const void *buf,
                       size_t len,
                       int flags) override;

    virtual ssize_t recvPacket(int sockfd,
                       void *buf,
                       size_t len,
                       int flags) override;

    virtual int closeConnection(int fd) override;

    virtual int getAddrInfo(const char *node,
                    const char *service,
                    const struct addrinfo *hints,
                    struct addrinfo **res) override;

    virtual void freeAddrInfo(struct addrinfo *res) override;

    virtual int createSocket(int domain,
                     int type,
                     int protocol) override;

    virtual int connectToRemote(int sockfd,
                        const struct sockaddr *addr,
                        socklen_t addrlen) override;
};

} /* Namespace cFunctions */

#endif /* PROTOCOLDEVELOPER_CNETCOMM_H */
