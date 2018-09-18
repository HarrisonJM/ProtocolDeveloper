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

#include "I_cNetComm.h"

namespace cFunctions
{

//! cNetComm Header file
class cNetComm : public I_cNetComm
{

public:
    //! constructor
    cNetComm() = default;
    //! destructor
    ~cNetComm() = default;
    //! man 2 send
    ssize_t sendPacket(int sockfd,
                       const void *buf,
                       size_t len,
                       int flags) override;
    //! man 2 recv
    ssize_t recvPacket(int sockfd,
                       void *buf,
                       size_t len,
                       int flags) override;
    //! man 2 close
    int closeConnection(int fd) override;
    //! man 3 getaddrinfo
    int getAddrInfo(const char *node,
                    const char *service,
                    const struct addrinfo *hints,
                    struct addrinfo **res) override;
    //! man 3 freeadrinfo
    void freeAddrInfo(struct addrinfo *res) override;
    //! man 2 socket
    int createSocket(int domain,
                     int type,
                     int protocol) override;
    //! man 2 remote
    int connectToRemote(int sockfd,
                        const struct sockaddr *addr,
                        socklen_t addrlen) override;
};

} /* Namespace cFunctions */

#endif /* PROTOCOLDEVELOPER_CNETCOMM_H */
