/*!
 * @brief Plugin interface for libCommunication
 *
 * @author hmarcks
 *
 * @addtogroup libnetworkCommunication
 * @{
 * @date 17/01/19
 */

#include <iostream>
#include "libnetworkCommunication/networkCommunication.h"

extern "C"
{
/*!
* @brief creates a new NetworkCommuncation object and returns its address
* @return A pointer to the new Communication object with it's default parameters
*/
networkCommunication::NetworkCommunication* createNewObject()
{
    return new networkCommunication::NetworkCommunication;
}
/*!
 * @brief Destroys a created plugin
 */
void destroyPlugin(networkCommunication::NetworkCommunication* in)
{
    delete in;
}

}
/*! @} */