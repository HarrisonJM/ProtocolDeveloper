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
    ssize_t send(int sockfd
                 , const void* buf
                 , size_t len
                 , int flags) override;
    //! man 2 recv
    ssize_t recv(int sockfd
                 , void* buf
                 , size_t len
                 , int flags) override;
    //! man 2 close
    int close(int fd) override;
    //! man 3 getaddrinfo
    int getaddrinfo(const char* node
                    , const char* service
                    , const struct addrinfo* hints
                    , struct addrinfo** res) override;
    //! man 3 freeadrinfo
    void freeaddrinfo(struct addrinfo* res) override;
    //! man 2 socket
    int socket(int domain
               , int type
               , int protocol) override;
    //! man 2 remote
    int connect(int sockfd
                , const struct sockaddr* addr
                , socklen_t addrlen) override;
};

} /* Namespace cFunctions */

#endif /* PROTOCOLDEVELOPER_CNETCOMM_H */
