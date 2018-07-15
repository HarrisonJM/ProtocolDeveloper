/*!
 * @brief Returns information/data to be sent after the user requests it
 *
 * @addtogroup testCaseHandler
 *
 * @date 30/Jun/18
 */

#include <string>
#include <rapidxml-1.13/rapidxml.hpp>
#include "variable.h"

#ifndef PROTOCOLDEVELOPER_TESTCASEPARSER_H
#define PROTOCOLDEVELOPER_TESTCASEPARSER_H

namespace testCaseHandler
{

class TestCaseParser
{
public:
    explicit TestCaseParser(std::string testFileName);
    ~TestCaseParser();

    //! @brief retunrs whether the testcase was successfully parsed
    bool IsSetup();
    //! @brief Moves to the next node
    bool MoveToNextEntry();
    //! @brief Returns the current Entry's Name
    void GetCurrentEntryName(std::string& entryName);
    //! @brief Gets the current attribute values
    bool GetCurrentEntryAttributes(std::string& attribiuteName,
                                   std::string& attributeValue);
    //! @brief Get free Data from entry
    void GetEntryData(std::string& entryData);
    //! @brief Get the current node type
    rapidxml::node_type GetEntryType();

    //! @brief Moves to the current nodes next sibling
    bool MoveToNexToSibling();
    //! @brief Returns the current Entry's Name
    void GetCurrentSiblingName(std::string& entryName);
    //! @brief Gets the current attribute values
    bool GetCurrentSiblingAttributes(std::string& attribiuteName,
                                   std::string& attributeValue);
    //! @brief Get free Data from entry
    void GetSiblingData(std::string& entryData);
    //! @brief Get the current node type
    rapidxml::node_type GetSiblingType();

private:
    bool isSetup;
    rapidxml::xml_node<>* root_node;
    rapidxml::xml_node<>* currentNode;
    rapidxml::xml_node<>* siblingNode;
};

} /* namespace */

#endif /*PROTOCOLDEVELOPER_TESTCASEPARSER_H*/