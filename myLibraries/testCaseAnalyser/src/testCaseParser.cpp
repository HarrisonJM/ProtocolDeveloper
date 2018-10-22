/*!
 * @brief Defines a parser that can walk/traverse an XML document tree
 *
 * When moving to child/sibling work exclusively on the top/current node and get
 * the "next sibling".
 *
 * When the lower level child is done, return to the previous level above.
 *
 * First child is node->first_node(). Subsequent nodes are node->next_sibling
 *
 * @addtogroup testCaseHandler
 *
 * @date 03/Jun/2018
 */



#include "testCaseParser.h"
#include "testCaseException.h"
#include <string>

namespace testCaseHandler
{

TestCaseParser::TestCaseParser(std::string testFileName)
{
    // setup doc
    // set current node to root node
}

TestCaseParser::~TestCaseParser()
{

}

bool TestCaseParser::MoveToNextEntry()
{
    rapidxml::xml_node<> *node = currentNode.top()->first_node();
    bool success = false;

    if(node != nullptr)
    {
        currentNode.pop();
        currentNode.push(node);
        success = true;
    }

    return success;
}

void TestCaseParser::GetCurrentEntryName(std::string &entryName)
{
    char* name = nullptr;
    currentNode.top()->name(name);

    entryName = name;
}
/*!
 * @brief Cycles over the current entries attributes
 * @param attributeName A reference to where to store the attribute's name
 * @param attributeValue A reference to where to store the attribute's value
 * @return False if more attributes, otherwise true
 */
bool TestCaseParser::GetCurrentEntryAttribute(std::string &attributeName,
                                              std::string &attributeValue)
{
    static bool notStarted = true;

    if(notStarted)
        currentAttribute.push(currentNode.top()->first_attribute());
    else
        currentAttribute.push(currentAttribute.top()->next_attribute());

    notStarted = false;

    // If the pointer is NULL, reset the stack
    if(!currentAttribute.top())
    {
        notStarted = true;
        while(!currentAttribute.empty())
            currentAttribute.pop();
    }
    else
    {
        attributeName  = currentAttribute.top()->name();
        attributeValue = currentAttribute.top()->name();
    }

    //entryName = name;
    return notStarted;
}

void TestCaseParser::GetEntryData(std::string &entryData)
{
    entryData = currentNode.top()->value();
}

rapidxml::node_type TestCaseParser::GetEntryType()
{
    return currentNode.top()->type();
}

bool TestCaseParser::MoveToSibling()
{
    static bool moved = true;
    if (! moved)
    {
        currentNode.push(currentNode.top()->first_node());
    }

    return moved;
}

bool TestCaseParser::MoveToNexTSibling()
{
    if(currentNode.top())
        currentNode.push(currentNode.top()->next_sibling());
    else
        return false;

    return true;
}

bool TestCaseParser::DoneWithSibling()
{
    currentNode.pop();
    return true;
}

} /* namespace testCaseAnalyser */