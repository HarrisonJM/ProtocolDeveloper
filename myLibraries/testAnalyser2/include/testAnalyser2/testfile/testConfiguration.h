/*!
 * @brief Represents a configuration object for configuring tests
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 03/01/19
 */


#ifndef PROTOCOLDEVELOPER_TESTCONFIGURATION_H
#define PROTOCOLDEVELOPER_TESTCONFIGURATION_H

#include <string>

namespace testAnalyser2
{
/*!
 * @brief A configuration object used to configure tests appropriately
 */
struct testConfiguration
{
    std::string _testName;
    std::string _protocol;
    std::string _tps;
    std::string _chaosMulti;
    std::string _secondsDuration;
    std::string _maxThreads;
    std::string _threadsPerInter;
    std::string _handler;
};
} /* namespace testAnalyser2 */

#endif /* PROTOCOLDEVELOPER_TESTCONFIGURATION_H */
