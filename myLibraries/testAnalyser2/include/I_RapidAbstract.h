/*!
 * @brief Interface for the abstraction layer between an xml parser and
 * the software
 *
 * @author hmarcks
 *
 * @addtogroup testAnalyser2
 *
 * @date 12/01/19
 *
 * @todo rapidabstract interface
 */

#ifndef PROTOCOLDEVELOPER_I_RAPIDABSTRACT_H
#define PROTOCOLDEVELOPER_I_RAPIDABSTRACT_H

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include <queue>

namespace testAnalyser2
{
class I_RapidAbstract
{
public:
    virtual ~I_RapidAbstract() = 0;
    /*!
     * @brief Gets the current node name
     * @return A char* contianing the node name
     */
    virtual const char* GetCurrentNodeName() = 0;
    /*!
     * @brief Moves to the next node (straight downly)
     * @return true on success, otherwise false
     */
    virtual bool MoveToNextNode() = 0;
    /*!
     * @brief Gets the Node's data (for a node_data type)
     * @return const char* containg the data
     */
    virtual const char* GetNodeValue() = 0;
    /*!
     * @brief Returns the size of the nodes value
     * @return the size of the value in the node
     */
    virtual std::size_t GetNodeValueSize() = 0;
    /*!
     * @brief Moves to the child node (diagonally)
     * @return true on success, otherwise false
     */
    virtual bool MoveToChild() = 0;
    /*!
     * @brief Returns to the previous highest node
     */
    virtual void ExitChild() = 0;
    /*!
     * @brief Selects an attribute to start reading that
     * @return true on success, otherwise false
     */
    virtual bool SelectAttribute() = 0;
    /*!
     * @brief Gets the next attribute in a node
     * @return true on success, otherwise false
     */
    virtual bool MoveToNextAttribute() = 0;
    /*!
     * @brief Gets the attribute's name
     * @return A char* contianing the node name
     */
    virtual const char* GetAttributeName() = 0;
    /*!
     * @brief Gets the attribute's value
     * @return A char* contianing the node name
     */
    virtual const char* GetAttributeValue() = 0;
    /*!
     * @brief Returns the current node's type
     * @return The node type that we have encountered as a
     * rapidxml::node_type::[type]
     */
    virtual rapidxml::node_type GetCurrentNodeType() = 0;
};
} /* namespace testAnalyser2 */

#endif /* PROTOCOLDEVELOPER_I_RAPIDABSTRACT_H */
