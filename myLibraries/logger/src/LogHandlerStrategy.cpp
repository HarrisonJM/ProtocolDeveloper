/*!
 * @brief Implemenation for the LogHandlerStrategy class
 *
 * It's purpose is to provide concreticity to an ostream object that can then
 * be passed into a logFile class
 *
 * @author hmarcks
 *
 * @date 28/08/18
 */

#include "LogHandlerStrategy.h"

namespace LoggerClasses
{

/*!
 * @brief selects the strategy by which a ostream will be made concrete
 * @param strat An enum dictating what strategy to return
 * @param fileName The name of the file we wish to open
 * @return A pointer to a concrete ostream
 */
std::unique_ptr<std::ostream> LogHandlerStrategy::returnOstream(StrategyEnums strat
                                                                , const std::string& fileName) const
{
    std::unique_ptr<std::ostream> newOSTream;
    switch (strat)
    {
        case StrategyEnums::FSTREAM:
            newOSTream = setupFstream(fileName);
            break;
        case StrategyEnums::SSTREAM:
            newOSTream = setupSStream();
            break;
        case StrategyEnums::STDERR:
            newOSTream = setupSTDERR();
            break;
        case StrategyEnums::STDOUT:
            newOSTream = setupSTDOUT();
            break;
        default:
            throw "TODO: logStrategy exceptions";
    }

    return std::move(newOSTream);
}
/*!
 * @brief Sets up a concrete fstream object for writing to
 * @param fileName The name of the file we wish to open
 * @return A pointer to an ostream object
 */
std::unique_ptr<std::ostream> LogHandlerStrategy::setupFstream(const std::string& fileName) const
{
    auto newStream_up = std::make_unique<std::fstream>();
    newStream_up->open(fileName,
                       std::ios_base::out | std::ios_base::app);

    return std::move(newStream_up);
}
/*!
 * @brief Sets up a string stream object for writing to
 * @return A pointer to an ostream object
 */
std::unique_ptr<std::ostream> LogHandlerStrategy::setupSStream() const
{
    auto newStream_up = std::make_unique<std::stringstream>();
    return std::move(newStream_up);
}
/*!
 * @brief Returns a pointer to a STDERR stream
 * @return A pointer to STDERR
 */
std::unique_ptr<std::ostream> LogHandlerStrategy::setupSTDERR() const
{
    auto unq_estream = std::make_unique<overloadStreamForSTD>(&std::cerr);
    return std::move(unq_estream);
}
/*!
 * @brief Returns a pointer to a stdout stream
 * @return  A pointer to STDOUT
 */
std::unique_ptr<std::ostream> LogHandlerStrategy::setupSTDOUT() const
{
    auto unq_outstream = std::make_unique<stdoutStream>();
    return std::move(unq_outstream);
}
} /* namespace LoggerClasses */