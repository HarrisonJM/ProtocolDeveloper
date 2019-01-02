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

//! interfaec for the cnetcomm class for mocking
class I_cNetComm
{

public:
    //! man 2 send()
    virtual ssize_t send(int sockfd
                         , const void* buf
                         , size_t len
                         , int flags) = 0;
    //! man 2 recv()
    virtual ssize_t recv(int sockfd
                         , void* buf
                         , size_t len
                         , int flags) = 0;
    //! man 2 close()
    virtual int close(int fd) = 0;
    //! man 2 getaddrinfo()
    virtual int getaddrinfo(const char* node
                            , const char* service
                            , const struct addrinfo* hints
                            , struct addrinfo** res) = 0;
    //! man 2 freeaddrinfo
    virtual void freeaddrinfo(struct addrinfo* res) = 0;
    //! man 2 socket
    virtual int socket(int domain
                       , int type
                       , int protocol) = 0;
    //! man 2 connect()
    virtual int connect(int sockfd
                        , const struct sockaddr* addr
                        , socklen_t addrlen) = 0;
};

} /* Namespace cFunctions */

#endif //PROTOCOLDEVELOPER_ICNETCOMM_H
