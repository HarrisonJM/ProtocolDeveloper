/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup
 *
 * @date 30/03/19
 */

#include <HelloWorldProtocol.h>
#include <iostream>

extern "C" {
/*!
* @brief creates a new NetworkCommuncation object and returns its address
* @return A pointer to the new Communication object with it's default parameters
*/
hwProt::HelloWorldProtocol* createNewObject()
{
    std::cout << "Create HW" << std::endl;
    return new hwProt::HelloWorldProtocol;
}
/*!
 * @brief Destroys a created plugin
 */
void destroyPlugin(hwProt::HelloWorldProtocol* in)
{
    delete in;
}

}