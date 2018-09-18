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
#include "I_communication.h"
#include <string>
#include <vector>

#ifndef PROTOCOLDEVELOPER_COMMUNICATIONHANDLER_H
#define PROTOCOLDEVELOPER_COMMUNICATIONHANDLER_H

namespace Communication
{
    class CommunicationHandler : public I_communication
    {
    public:
        CommunicationHandler();
        ~CommunicationHandler();
        void RegisterComms();

    private:

    };
}

#endif //PROTOCOLDEVELOPER_COMMUNICATIONHANDLER_H
