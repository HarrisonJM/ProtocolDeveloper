/*!
 * @brief Handles communication
 *
 * Deals with outgoing and incoming communication and passes the information
 * to whatever requires it
 *
 * @addtogroup CommunicationHandler
 *
 * @date March 2018
 */
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "CommunicationHandler.h"

namespace CommunicationHandler
{
    /*!
     * @brief Constructor
     */
    CommunicationHandler::CommunicationHandler()
    : port("9687"),
      address("127.0.0.1"),
      outSocket(-1)
    {

    }

    /*!
     * @brief Destructor
     */
    CommunicationHandler::~CommunicationHandler()
    {

    }

    /*!
     * @brief sends the provided data
     *
     * @param payLoad_p A pointer to the information we want to send
     * @param size The size of the information we want to send
     * @return True on success, otherwise false
     */
	bool CommunicationHandler::SendData(void *payLoad_p, int size)
	{

        return true;
	}

    /*!
     * @brief Receives data ready to pass on
     *
     * @param payLoad_p A pointer to where to store the data
     * @param size The size of the received data
     *
     * @return None
     */
	void CommunicationHandler::ReceiveData(void *payLoad_p, int size)
	{

	}

    /*!
     * @brief establishes a connection with the remote
     *
     * @return True on success, otherwise false
     */
    bool CommunicationHandler::EstablishConnection()
    {
        SetupAddrInfo();
        DoSocketAndConnect();
        return true;
    }

    /*!
     * @brief Disconnects form the remote
     *
     * @return None
     */
    void CommunicationHandler::Disconnect()
    {

    }

    /*!
     * @brief setups up the ProtDev connection/client Information
     *
     * @return none
     */
    void CommunicationHandler::SetupAddrInfo()
    {
        int status = 0;
        addrinfo hints = {0};

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC; // Either ipv4 or 6
        hints.ai_socktype = SOCK_STREAM; //tcp
        // p
        hints.ai_flags = AI_PASSIVE; // Do my IP for me

        if (0 != (status = getaddrinfo(address.c_str(), port.c_str(), &hints, &servinfo)))
        {
            fprintf(stderr, "getaddr failure in SetupAddrInfo(): %s" , gai_strerror(status));
            exit(1);
        }
    }

    /*!
     * @brief sets up the socket and connects to the remote
     *
     * @todo Needs to work on datagram too
     *
     * @return None
     */
    void CommunicationHandler::DoSocketAndConnect()
    {
        addrinfo *p;
        // loop through all the results and bind to the first we can
        for(p = servinfo; p != nullptr; p = p->ai_next)
        {
            if (-1 == (outSocket = socket(p->ai_family, p->ai_socktype, p->ai_protocol)))
            {
                perror("server: socket");
                continue;
            }

            if (-1 == connect(outSocket, p->ai_addr, p->ai_addrlen))
            {
                close(outSocket);
                perror("client: connect");
                continue;
            }

            break;
        }
    }
}