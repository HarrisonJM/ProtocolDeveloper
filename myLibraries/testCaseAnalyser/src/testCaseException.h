/*!
 * @brief testCase Exceptions
 *
 * @addtogroup
 *
 * @date 12/07/18
 */


#ifndef PROTOCOLDEVELOPER_TESTCASEEXCEPTION_H
#define PROTOCOLDEVELOPER_TESTCASEEXCEPTION_H

#include <exception>

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

class parser_badType : public testCaseException
{
public:
    const char* what()
    {
        return "Bad/unrecognised XML type in model";
    }
};

class parser_badNodeName : public testCaseException
{
public:
    const char* what()
    {
        return "Bad node name given";
    }
};

class parser_NullNode : public testCaseException
{
public:
    const char* what()
    {
        return "Null Node returned";
    }
};

class parser_NullAttribute : public testCaseException
{
public:
    const char* what()
    {
        return "Null attribute returned";
    }
};

}

#endif /*PROTOCOLDEVELOPER_TESTCASEEXCEPTION_H*/
