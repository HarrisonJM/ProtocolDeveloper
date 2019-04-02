/*!
 * @brief Plugin interface for libCommunication
 *
 * @author hmarcks
 *
 * @addtogroup libnetworkCommunication
 *
 * @date 17/01/19
 */

#include <iostream>
#include "libnetworkCommunication/libNetworkCommunication.h"

extern "C"
{
/*!
* @brief creates a new NetworkCommuncation object and returns its address
* @return A pointer to the new Communication object with it's default parameters
*/
libNetworkCommunication::libNetworkCommunication* createNewObject()
{
    return new libNetworkCommunication::libNetworkCommunication;
}
/*!
 * @brief Destroys a created plugin
 */
void destroyPlugin(libNetworkCommunication::libNetworkCommunication* in)
{
    delete in;
}

}
/*! @} */