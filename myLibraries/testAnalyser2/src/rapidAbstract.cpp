/*!
 * @brief Provides an abstraction between rapidxml and the library. Improves EoU
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 02/01/19
 */

#include "rapidAbstract.h"

namespace testAnalyser2
{

/*!
 * @brief Constructor. Sets up the document ready to be analysed
 * @param filePath The path to the xml file
 */
RapidAbstract::RapidAbstract(std::string const& filePath)
{
    /* Reads the xml file into a vector */
    std::ifstream xmlFile(filePath);
    std::vector<char> buffer((std::istreambuf_iterator<char>(xmlFile))
                             , std::istreambuf_iterator<char>());
    buffer.push_back('\0');

    /* Parses the entire document ready to be analysed */
    /* 0 is the template means default parse flags */
    _doc.parse<0>(&buffer[0]);

    _rootNode = _doc.first_node();
    _currentNode.push(_rootNode);
}
/*!
 * @brief Destructor
 */
RapidAbstract::~RapidAbstract()
{
    _doc.clear();
}
/*!
 * @brief Gets the current node name
 * @return A char* contianing the node name
 */
const char* RapidAbstract::GetCurrentNodeName()
{
    return _currentNode.top()->name();
}
/*!
 * @brief Moves to the next available node
 * @return true for success, otherwise false
 */
bool RapidAbstract::MoveToNextNode()
{
    bool returnVal = false;
    rapidxml::xml_node<>* newNode;
    newNode = _currentNode.top()->next_sibling();

    if (newNode)
    {
        returnVal = true;
        _currentNode.pop();
        _currentNode.push(newNode);
    }

    return returnVal;
}
/*!
 * @brief Moves to the child node (diagonally).
 * @return true on success, otherwise false (no children or failure)
 */
bool RapidAbstract::MoveToChild()
{
    bool retval = false;
    rapidxml::xml_node<>* childNode;
    childNode = _currentNode.top()->first_node();

    if (childNode)
    {
        _currentNode.push(childNode);
        retval = true;
    }

    return retval;
}
/*!
 * @brief Pops of the current node to return to the last highest node
 */
void RapidAbstract::ExitChild()
{
    _currentNode.pop();
}
/*!
 * @brief Gets the Node's data (for a node_data type)
 * @return const char* containg the data
 */
const char* RapidAbstract::GetNodeValue()
{
    return _currentNode.top()->value();
}
/*!
 * @brief Returns the size of the node's value
 * @return The size of the value
 */
std::size_t RapidAbstract::GetNodeValueSize()
{
    return _currentNode.top()->value_size();
}
/*!
 * @brief Selects an attribute to start reading that
 * @return true on success, otherwise false
 */
bool RapidAbstract::SelectAttribute()
{
    bool returnVal = false;
    rapidxml::xml_attribute<>* newAttribute = _currentNode.top()->first_attribute();

    if (newAttribute)
    {
        returnVal = true;
        _currentAttribute = newAttribute;
    }

    return returnVal;
}
/*!
 * @brief Gets the next attribute in a node. Checks to make sure an
 * attribute is selected. If null is found, resets the current attribute
 *
 * @return true on success, otherwise false
 */
bool RapidAbstract::MoveToNextAttribute()
{
    bool returnVal = false;

    if (_currentAttribute)
    {
        rapidxml::xml_attribute<>* newAttribute = _currentAttribute->next_attribute();
        if (newAttribute)
        {
            _currentAttribute = newAttribute;
            returnVal = true;
        }
    }

    return returnVal;
}
/*!
 * @brief Gets the attribute's name
 * @return A char* containing the node name
 */
const char* RapidAbstract::GetAttributeName()
{
    if (_currentAttribute)
    {
        return _currentAttribute->name();
    }

    return nullptr;
}
/*!
 * @brief Gets the attribute's value
 * @return A char* containing the node name
 */
const char* RapidAbstract::GetAttributeValue()
{
    if (_currentAttribute)
    {
        return _currentAttribute->value();
    }
    return nullptr;
}
/*!
 * @brief Returns the current node's type
 * @return The node type that we have encountered as a
 * rapidxml::node_type::[type]
 */
rapidxml::node_type RapidAbstract::GetCurrentNodeType()
{
    return _currentNode.top()->type();
}
} /* namespace testAnalyser2 */