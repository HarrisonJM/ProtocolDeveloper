/*!
 * @brief Handles exceptions in the parser. Improves hiding from rapidxml
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 03/01/19
 *
 * @todo Figure out how to collapse the where() from the rapidxml::parse_error into a single what()
 */


#ifndef PROTOCOLDEVELOPER_ANALYSISEXCEPTION_H
#define PROTOCOLDEVELOPER_ANALYSISEXCEPTION_H

#include <exception>
#include <rapidxml/rapidxml.hpp>
#include <cstring>

namespace testAnalyser2
{
/*!
 * @brief Handles exceptions in the initial parsing
 */
class parserException
    : public rapidxml::parse_error
{
    /*! @todo this */
};
/*!
 * @brief Base analyser exception class
 */
class baseAnalyser_Exception
    : public std::exception
{
public:
    explicit baseAnalyser_Exception(const char* info
                                    , size_t length)
        : _info(info)
          , _length(length)
    {
    }

    ~baseAnalyser_Exception()
    {
    }

    virtual const char* what() = 0;
protected:

    const char* _BuildError(const char* errorMessage)
    {
        std::strcat(_error
                    , errorMessage);
        std::strncat(_error
                     , _info
                     , _length);
        return _error;
    }
private:
    const char* _info;
    char _error[16384];
    const size_t _length;
};
/*!
 * @brief If the rapid_xml::node type is incorrect at that time
 */
class analyserIncorrectXMLType_Exception
    : public baseAnalyser_Exception
{
public:
    explicit analyserIncorrectXMLType_Exception(const char* info
                                                , size_t length)
        : baseAnalyser_Exception(info
                                 , length)
    {
    }

    virtual const char* what()
    {
        return _BuildError("Incorrect tag type (Not node, attribute or data). Node value: ");
    }
};
/*!
 * @brief The node just found is not at all in the correct place/between the correct tags e.g. config in a datapoint
 */
class analyserNodeInWrongPlace_Exception
    : public baseAnalyser_Exception
{
public:
    explicit analyserNodeInWrongPlace_Exception(const char* info
                                                , size_t length)
        : baseAnalyser_Exception(info
                                 , length)
    {
    }

    virtual const char* what()
    {
        return _BuildError("Tag found in a strange place: ");
    }
};
/*!
 * @brief Malformed testcase
 */
class analyserMalformedTestCase_Exception
    : public baseAnalyser_Exception
{
public:
    explicit analyserMalformedTestCase_Exception(const char* info)
        : baseAnalyser_Exception(info
                                 , std::strlen(info))
    {
    }

    virtual const char* what()
    {
        return _BuildError("Testcase is odd: ");
    }
};
/*!
 * @brief The parser has returned a NULL value
 */
class analyserParserNullReturn_Exception
    : public baseAnalyser_Exception
{
public:
    explicit analyserParserNullReturn_Exception(const char* info)
        : baseAnalyser_Exception(info
                                 , std::strlen(info))
    {
    }

    virtual const char* what()
    {
        return _BuildError("Parser has returned a NULL value Line: ");
    }
};
/*!
 * @brief An incorrect node/tag pair has been given
 */
class analyserWrongTagUsedInNode_Exception
    : public baseAnalyser_Exception
{
public:
    explicit analyserWrongTagUsedInNode_Exception(const char* info)
        : baseAnalyser_Exception(info
                                 , std::strlen(info))
          , _info(info)
    {
    }

    virtual const char* what()
    {
        return _BuildError("Wrong tag given in node. ");
    }

    const char* _info;
};
/*!
 * @brief An incorrect node/tag pair has been given
 */
class analyserFileDoesntExist_Exception
    : public baseAnalyser_Exception
{
public:
    explicit analyserFileDoesntExist_Exception(const char* info)
        : baseAnalyser_Exception(info
                                 , std::strlen(info))
          , _info(info)
    {
    }

    virtual const char* what()
    {
        return _BuildError("File does not exist! ");
    }

    const char* _info;
};
} /* namespace testAnalyser2 */

#endif /* PROTOCOLDEVELOPER_ANALYSISEXCEPTION_H */
