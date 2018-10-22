/*!
 * @brief Returns information/data to be sent after the user requests it
 *
 * @addtogroup testCaseHandler
 *
 * @date 30/Jun/18
 */

#include <string>
#include <stack>
#include <rapidxml-1.13/rapidxml.hpp>
#include "variable.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "string"

#ifndef PROTOCOLDEVELOPER_TESTCASEPARSER_H
#define PROTOCOLDEVELOPER_TESTCASEPARSER_H

namespace testCaseHandler
{

class TestCaseParser
{
public:
    explicit TestCaseParser(std::string testFileName);
    ~TestCaseParser();

    //! @brief Moves to the next node
    bool MoveToNextEntry();
    //! @brief Returns the current Entry's Name
    void GetCurrentEntryName(std::string& entryName);
    //! @brief Gets the current attribute values
    bool GetCurrentEntryAttribute(std::string &attributeName,
                                  std::string &attributeValue);
    //! @brief Get free Data from entry
    void GetEntryData(std::string& entryData);
    //! @brief Get the current node type
    rapidxml::node_type GetEntryType();

    //! Grabs the sibling and moves the current node onto the stack
    bool MoveToSibling();
    //! Advances to the next sibling
    bool MoveToNexTSibling();
    //! Discards current node with previous node and pops off the stack
    bool DoneWithSibling();

private:
    bool isSetup;
    rapidxml::xml_node<>* root_node;
    std::stack<rapidxml::xml_node<>*> currentNode;
    std::stack<rapidxml::xml_attribute<>*> currentAttribute;
};

} /* namespace */

#endif /*PROTOCOLDEVELOPER_TESTCASEPARSER_H*/