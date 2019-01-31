/*!
 * @brief ProtocolInterface
 *
 * Defines the interface that will be instantiated for protocols to
 * communicate with the core
 *
 * THE WAY IT WORKS IS:
 *
 * Test handler will request data generation from protocol
 * Testcase will request data
 * Testcase will pass data to comms ahndler to be sent
 * Comms handler will pass information back to the test
 * the test will pass it to the protocol to be decode (And it be returned)
 * Finally the test will log what the result was
 *
 * @addtogroup Protocol
 *
 * @date March 2018
 */
#ifndef PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H
#define PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H

#include <testAnalyser2/testfile/dataPoint.h>
#include <boost/shared_ptr.hpp>

namespace Protocol
{
/*!
 * @brief struct that we may or may not use to pass around information
 */
struct DataStruct
{
    //! A pointer to the data
    void* _data_p;
    //! The size of the data
    size_t _size;
};
/*!
 * @brief Base Protocol interface
 */
class I_protocolInterface
{
public:
    /*! @brief Destructor */
    virtual ~I_protocolInterface() = default;
    /*!
     * @brief Decodes the data returned from the target
     * @param payLoad The payload received from the target
     */
    virtual void DecodeResult(std::shared_ptr<DataStruct> payLoad) = 0;
    /*!
     * @brief I don't think this does anything?
     * @return A pointer to a struct of data and sizes
     */
    virtual std::shared_ptr<DataStruct> GetDataToSend() = 0;
    /*!
     * @brief The final result of the returned data
     * @return The returned data
     */
    virtual std::shared_ptr<DataStruct> GetResult() = 0;
    /*!
     * @brief The result code returned/calculated
     * @return Result code
     */
    virtual int GetResultCode() = 0;
    /*!
     * @brief Sets the protocols datapoints
     * @param testDP The datapoints we're using
     */
    virtual void SetDataPoints(testAnalyser2::dataPoint testDP) = 0;
};
} /* namespace Protocol */
#endif //PROTOCOLDEVELOPER_PROTOCOLINTERFACE_H
