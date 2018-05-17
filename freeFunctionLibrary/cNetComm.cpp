/*!
 * @brief Wrapper class to allow mocking the network communication libraries
 * provided from C
 *
 * @addtogroup cMocking
 *
 * @date 09/05/2018
 */

#include "cNetComm.h"

#include <unistd.h>

namespace cFunctions
{
/*!
 * @brief Wrapper for C function send()
 * @param sockfd The File Descriptor of where we wish to send the packet
 * @param buf The Packet itself
 * @param len The size of the packet
 * @param flags Additional information
 * @return The number of bytes sent, -1 on error
 */
ssize_t cNetComm::sendPacket(int sockfd,
                             const void *buf,
                             size_t len,
                             int flags)
{
    return send(sockfd,
                buf,
                len,
                flags);
}

/*!
 * @brief Wrapper for C function recv()
 * @param sockfd The File Descriptor of where we wish to send the packet
 * @param buf The Packet itself
 * @param len The size of the packet
 * @param flags Additional information
 * @return The number of bytes sent, -1 on error
 */
ssize_t cNetComm::recvPacket(int sockfd,
                             void *buf,
                             size_t len,
                             int flags)
{
    return recv(sockfd,
                buf,
                len,
                flags);
}

/*!
 * @brief Wrapper for C function close()
 * @param fd The File descriptor for the socket we wish to close
 * @return 0 on success, else -1
 */
int cNetComm::closeConnection(int fd)
{
    return close(fd);
}

/*!
 * @brief Wrapper for C function getaddrinfo
 * @param node A pointer to the address of the remote we wish to connect to
 * @param service The port we wish to connect on
 * @param hints Any hints we want to supply to get a more specific address range
 * @param res The resultant struct of addresses as a linked list
 * @return 0 on success, or a non-zero error code: getaddrinfo(3)
 */
int cNetComm::getAddrInfo(const char *node,
                          const char *service,
                          const struct addrinfo *hints,
                          struct addrinfo **res)
{
    return getaddrinfo(node,
                       service,
                       hints,
                       res);
}

/*!
 * @brief Wrapper for C function freeaddrinfo
 * @param res The linked list result we wish to free
 */
void cNetComm::freeAddrInfo(struct addrinfo *res)
{
    freeaddrinfo(res);
}

/*!
 * @brief Wrapper for C function socket()
 * @param domain The ai_family
 * @param type The ai_socktype
 * @param protocol ai_protocol
 * @return A new socket file descriptor for us to use to communicate
 */
int cNetComm::createSocket(int domain,
                           int type,
                           int protocol)
{
    return socket(domain,
                  type,
                  protocol);
}

/*!
 * @brief Wrapper for C function connect()
 * @param sockfd  The socket file descriptor for us to communicate on
 * @param addr
 * @param addrlen
 * @return
 */
int cNetComm::connectToRemote(int sockfd,
                              const struct sockaddr *addr,
                              socklen_t addrlen)
{
    return connect(sockfd,
                   addr,
                   addrlen);
}

}