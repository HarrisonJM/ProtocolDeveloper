/*!
 * @brief testCase Exceptions
 *
 * @addtogroup
 *
 * @date 12/07/18
 */


#ifndef PROTOCOLDEVELOPER_TESTCASEEXCEPTION_H
#define PROTOCOLDEVELOPER_TESTCASEEXCEPTION_H

namespace testCaseHandler
{

class testCaseException : public std::exception
{
public:
    virtual const char* what()
    {
        return "Test Case Parser has encountered an error";
    }
};

class parser_TooManyData : public testCaseException
{
public:
    const char* what()
    {
        return "Too many data forms per datapoint";
    }
};

class parser_SyntaxError : public testCaseException
{
public:
    const char* what()
    {
        return "Syntax wrong";
    }
};

}

#endif /*PROTOCOLDEVELOPER_TESTCASEEXCEPTION_H*/
