/*!
 * @brief Defines a generic process for the DAEMONISER to run
 *
 * @author hmarcks
 * @date 14/04/19
 * @addtogroup serviceLib
 * @{
 * @addtogroup interfaces
 * @{
 */


#ifndef __PROTOCOLDEVELOPER_I_DEAMONISER_H__
#define __PROTOCOLDEVELOPER_I_DEAMONISER_H__

namespace serviceLib
{

class I_process
{
public:
    virtual void RunProcess() = 0;
};

} /* namespace serviceLib */
/*! @} @} */
#endif /* __PROTOCOLDEVELOPER_I_DEAMONISER_H__ */
