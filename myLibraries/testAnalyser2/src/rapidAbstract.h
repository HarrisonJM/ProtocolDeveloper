/*!
 * @brief Provides an abstraction between rapidxml and the library. Improves EoU.
 *
 * Acts as a "context" for the xml document. Allows a user to more easily drill
 * down. Access nodes, data, and values more directly and hides a
 * lot of the messy types
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 02/01/19
 *
 * @todo rapidabstract interface
 */

#ifndef PROTOCOLDEVELOPER_RAPIDABSTRACT_H
#define PROTOCOLDEVELOPER_RAPIDABSTRACT_H

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include <stack>

#include <I_RapidAbstract.h>

namespace testAnalyser2
{

class RapidAbstract
    : public I_RapidAbstract
{
public:
    explicit RapidAbstract(std::string const& filePath);
    ~RapidAbstract() override;
    /*!
     * @brief Gets the current node name
     * @return A char* containing the node name
     */
    const char* GetCurrentNodeName() override;
    /*!
     * @brief Moves to the next node (straight downly)
     * @return true on success, otherwise false
     */
    bool MoveToNextNode() override;
    /*!
     * @brief Gets the Node's data (for a node_data type)
     * @return const char* containing the data
     */
    const char* GetNodeValue() override;
    /*!
     * @brief Returns the size of the nodes value
     * @return the size of the value in the node
     */
    std::size_t GetNodeValueSize() override;
    /*!
     * @brief Moves to the child node (diagonally)
     * @return true on success, otherwise false
     */
    bool MoveToChild() override;
    /*!
     * @brief Returns to the previous highest node
     */
    void ExitChild() override;
    /*!
     * @brief Selects an attribute to start reading that
     * @return true on success, otherwise false
     */
    bool SelectAttribute() override;
    /*!
     * @brief Gets the next attribute in a node
     * @return true on success, otherwise false
     */
    bool MoveToNextAttribute() override;
    /*!
     * @brief Gets the attribute's name
     * @return A char* containing the node name
     */
    const char* GetAttributeName() override;
    /*!
     * @brief Gets the attribute's value
     * @return A char* containing the node name
     */
    const char* GetAttributeValue() override;
    /*!
     * @brief Returns the current node's type
     * @return The node type that we have encountered as a
     * rapidxml::node_type::[type]
     */
    rapidxml::node_type GetCurrentNodeType() override;
private:
    /*!
     * @brief The rapidxml document file
     */
    rapidxml::xml_document<> _doc;
    /*!
     * @brief The last root node
     */
    rapidxml::xml_node<>* _rootNode;
    /*!
     * @brief The node we're currently on
     */
    std::stack<rapidxml::xml_node<>*> _currentNode;
    /*!
     * @brief Represents the current attribute we're on
     */
    rapidxml::xml_attribute<>* _currentAttribute;
};
} /* namespace testAnalyser2 */

#endif /* PROTOCOLDEVELOPER_RAPIDABSTRACT_H */
