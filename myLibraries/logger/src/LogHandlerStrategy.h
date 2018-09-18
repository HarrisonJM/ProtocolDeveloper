/*!
 * @brief Decides the strategy of the loghandler, implemented mainly, for now,
 * for testing purposes
 *
 * @date 28/08/18
 *
 * @author hmarcks
 *
 * @addtogroup logger
 *
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

namespace LoggerClasses {

class LogHandlerStrategy : public I_LogStrategy
{
public:
    //! Constructor
    explicit LogHandlerStrategy() = default;
    //! Switchcase, strategy selector
    std::unique_ptr<std::ostream> returnOstream(StrategyEnums strat,
                                                std::string fileName) const override;
private:
    //! Fstream factory
    std::unique_ptr<std::ostream> setupFstream(std::string fileName) const;
    //! String String factory
    std::unique_ptr<std::ostream> setupSStream() const;
    //! Stream to stderr
    std::unique_ptr<std::ostream> setupSTDERR() const;
    //! Stream to stdout
    std::unique_ptr<std::ostream> setupSTDOUT() const;

    //! overloads << to allow streaming to stdout/stderr, may not work
    class overloadStreamForSTD : public std::ostream
    {
    public:
        overloadStreamForSTD(std::ostream* oStream_in)
        : _outStrategy(oStream_in)
        { }
        template<class T>
        overloadStreamForSTD& operator<<(const T& message)
        {
            _outStrategy << message;
            return *this;
        }
    private:
        std::ostream* _outStrategy;
    };

    //! overloads specifically for stdout, stuff and things
    class stdoutStream : public std::ostream
    {
    public:

        template<class T>
        stdoutStream& operator<<(const T& obj)
        {
            std::cout << obj;
            return *this;
        }
    };
};

} /* namespace LoggerClasses */
#endif //PROTOCOLDEVELOPER_LOGHANDLERSTRATEGY_H
