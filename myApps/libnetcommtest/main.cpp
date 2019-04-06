/*!
 * @brief
 *
 * @author hmarcks
 *
 * @addtogroup
 *
 * @date 06/04/19
 */

#include <libnetworkCommunication/libNetworkCommunication.h>
#include <iostream>

int main()
{
    libNetworkCommunication::libNetworkCommunication n;
    n.EstablishConnection();

    char str[128];
    n.SendData(str
               , 128);
    n.ReceiveData(str
                  , 128);
    std::cout << str << std::endl;

    return 0;
}