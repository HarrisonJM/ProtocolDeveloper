/*!
 * @brief Interface class for the C socket wrapper class
 *
 * @addtogroup cMocking
 *
 * @date 10/05/18
 */

#ifndef PROTOCOLDEVELOPER_ICNETCOMM_H
#define PROTOCOLDEVELOPER_ICNETCOMM_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

namespace cFunctions
{

class I_cNetComm
{

public:

    virtual ssize_t sendPacket(int sockfd,
                       const void *buf,
                       size_t len,
                       int flags) = 0;

    virtual ssize_t recvPacket(int sockfd,
                       void *buf,
                       size_t len,
                       int flags) = 0;

    virtual int closeConnection(int fd) = 0;

    virtual int getAddrInfo(const char *node,
                    const char *service,
                    const struct addrinfo *hints,
                    struct addrinfo **res) = 0;

    virtual void freeAddrInfo(struct addrinfo *res) = 0;

    virtual int createSocket(int domain,
                     int type,
                     int protocol) = 0;

    virtual int connectToRemote(int sockfd,
                        const struct sockaddr *addr,
                        socklen_t addrlen) = 0;
};

} /* Namespace cFunctions */

#endif //PROTOCOLDEVELOPER_ICNETCOMM_H
