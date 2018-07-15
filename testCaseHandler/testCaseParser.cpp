/*!
 * @brief Defines a parser that can walk/traverse an XML document tree
 *
 * @addtogroup testCaseHandler
 *
 * @date 03/Jun/2018
 */


#include "testCaseParser.h"
#include <string>

namespace testCaseHandler
{

TestCaseParser::TestCaseParser(std::string testFileName)
{

}

TestCaseParser::~TestCaseParser()
{

}
bool TestCaseParser::IsSetup()
{
    return false;
}
bool TestCaseParser::MoveToNextEntry()
{
    return false;
}
void TestCaseParser::GetCurrentEntryName(std::string &entryName)
{

}
bool TestCaseParser::GetCurrentEntryAttributes(std::string &attribiuteName,
                                               std::string &attributeValue)
{
    return false;
}
void TestCaseParser::GetEntryData(std::string &entryData)
{

}
rapidxml::node_type TestCaseParser::GetEntryType()
{
    return rapidxml::node_data;
}
bool TestCaseParser::MoveToNexToSibling()
{
    return false;
}
void TestCaseParser::GetCurrentSiblingName(std::string &entryName)
{

}
bool TestCaseParser::GetCurrentSiblingAttributes(std::string &attribiuteName,
                                                 std::string &attributeValue)
{
    return false;
}
void TestCaseParser::GetSiblingData(std::string &entryData)
{

}
rapidxml::node_type TestCaseParser::GetSiblingType()
{
    return rapidxml::node_data;
};

//getXMLDoc();

} /* CHANGEME */