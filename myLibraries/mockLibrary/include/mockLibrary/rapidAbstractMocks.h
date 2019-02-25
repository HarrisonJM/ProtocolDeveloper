/*!
 * @brief gmock mocks for the rapidAbstract class
 *
 * @author hmarcks
 *
 * @addtogroup mocksLibrary
 *
 * @date 22/02/19
 */

#ifndef PROTOCOLDEVELOPER_RAPIDABSTRACTMOCKS_H
#define PROTOCOLDEVELOPER_RAPIDABSTRACTMOCKS_H

#include "gmock/gmock.h"

#include <I_RapidAbstract.h>

namespace testAnalyser2
{
class rapidAbstractMocks
    : public I_RapidAbstract
{
    rapidAbstractMocks() = default;

    MOCK_CONST_METHOD0(GetCurrentNodeName
                       , const char*());
    MOCK_CONST_METHOD0(MoveToNextNode
                       , bool*());
    MOCK_CONST_METHOD0(GetNodeValue
                       , const char*());
    MOCK_CONST_METHOD0(GetNodeValueSize
                       , std::size_t());
    MOCK_CONST_METHOD0(MoveToChild
                       , bool());
    MOCK_CONST_METHOD0(ExitChild
                       , void());
    MOCK_CONST_METHOD0(SelectAttribute
                       , bool());
    MOCK_CONST_METHOD0(MoveToNextAttribute
                       , bool());
    MOCK_CONST_METHOD0(GetAttributeName
                       , const char*());
    MOCK_CONST_METHOD0(GetAttributeValue
                       , const char*());
    MOCK_CONST_METHOD0(GetCurrentNodeType
                       , rapidxml::node_type());
};
} /* namespace testAnalyser2 */

#endif /* PROTOCOLDEVELOPER_RAPIDABSTRACTMOCKS_H */
