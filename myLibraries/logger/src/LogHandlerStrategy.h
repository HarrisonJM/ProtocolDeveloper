/*!
 * @brief Decides the strategy of the loghandler, implemented mainly, for now,
 * for testing purposes
 *
 * @date 28/08/18
 *
 * @author hmarcks
 *
 * @addtogroup logger
 * @{
 * @todo Add register method So that users can add their own handling strategy
 */

#ifndef PROTOCOLDEVELOPER_LOGHANDLERSTRATEGY_H
#define PROTOCOLDEVELOPER_LOGHANDLERSTRATEGY_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include "logger/loggerUtility.h"
#include "I_LogStrategy.h"

namespace logger
{

class LogHandlerStrategy
    : public I_LogStrategy
{
public:
    //! Constructor
    explicit LogHandlerStrategy() = default;
    /*!
     * @brief returns the desired std::ostream base based on a StrategyEnum
     * @param strat The strategy we wish to select
     * @param fileName The filename of the file we wish to open
     * @return A unique_ptr contining the stream we wish to use
     */
    std::unique_ptr<std::ostream> returnOstream(StrategyEnums strat
                                                , const std::string& fileName) const override;
private:
    /*!
     * @brief setsup a filestream for use
     * @param fileName the filename of the log
     * @return A unique_ptr contianing the filestream
     */
    std::unique_ptr<std::ostream> setupFstream(const std::string& fileName) const;
    /*!
     * @brief String stream factory
     * @return A unique_ptr contianing the stringstream
     */
    std::unique_ptr<std::ostream> setupSStream() const;
    /*!
     * @brief stderr stream factory
     * @return A unique_ptr contianing the stderr
     */
    std::unique_ptr<std::ostream> setupSTDERR() const;
    /*!
     * @brief stderr stream factory
     * @return A unique_ptr contianing the stdout
     */
    std::unique_ptr<std::ostream> setupSTDOUT() const;

    //! overloads << to allow streaming to stdout/stderr, may not work
    class overloadStreamForSTD
        : public std::ostream
    {
    public:
        /*!
         * @brief Constructor for the overload stream package
         * @param oStream_in The ostream we wish to pass in
         */
        overloadStreamForSTD(std::ostream* oStream_in)
            : _outStrategy(oStream_in)
        {}
        /*!
         * @brief operator<< overload
         * @tparam T The type the output should take
         * @param message The message we wish to print
         * @return A reference to the stream
         */
        template<class T>
        overloadStreamForSTD& operator<<(const T& message)
        {
            _outStrategy << message;
            return *this;
        }
    private:
        //! A pointer to the ostream we want to use
        std::ostream* _outStrategy;
    };
    /*!
     * @brief Constructor for the overload stream package
     * @param oStream_in The ostream we wish to pass in
     */
    class stdoutStream
        : public std::ostream
    {
    public:
        /*!
         * @brief operator<< overload
         * @tparam T The type the output should take
         * @param message The message we wish to print
         * @return A reference to the stream
         */
        template<class T>
        stdoutStream& operator<<(const T& obj)
        {
            std::cout << obj;
            return *this;
        }
    };
};

} /* namespace logger */
/*! @} */
#endif //PROTOCOLDEVELOPER_LOGHANDLERSTRATEGY_H
