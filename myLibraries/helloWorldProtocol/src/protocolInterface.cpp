/*!
 * @brief Defines the DLL boundary
 *
 * @author hmarcks
 *
 * @date 30/03/19
 * @addtogroup helloWorldProtocol
 * @{
 */

#include <HelloWorldProtocol.h>
#include <iostream>

extern "C" {
/*!
* @brief creates a new NetworkCommuncation object and returns its address
* @return A pointer to the new Communication object with it's default parameters
*/
helloWorldProtocol::HelloWorldProtocol* createNewObject()
{
    std::cout << "Create HW" << std::endl;
    return new helloWorldProtocol::HelloWorldProtocol;
}
/*!
 * @brief Destroys a created plugin
 */
void destroyPlugin(helloWorldProtocol::HelloWorldProtocol* in)
{
    delete in;
}

}

/*! @} */