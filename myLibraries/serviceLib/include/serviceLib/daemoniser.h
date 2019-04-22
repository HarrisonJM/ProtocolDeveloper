/*!
 * @brief Handles creating the daemon process in accordance with "Advanced Programming in the UNIX Environment, 3rd edition"
 *, Chapter 13
 * @author hmarcks
 * @date 14/04/19
 * @addtogroup serviceLib
 * @{
 */

#ifndef __PROTOCOLDEVELOPER_DAEMONISER_H__
#define __PROTOCOLDEVELOPER_DAEMONISER_H__

namespace serviceLib
{

class Daemoniser
{
public:
    Daemoniser();
    ~Daemoniser();

    void Daemonise(const char* cmd);
private:

};

} /* namespace serviceLib */
/*! @} */
#endif /*__PROTOCOLDEVELOPER_DAEMONISER_H__*/
