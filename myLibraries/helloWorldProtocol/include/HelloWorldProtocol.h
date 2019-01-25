/*!
 * @brief HelloWorldProtocol
 *
 * The HelloWorldProtocol data generation and decoder, decalration
 *
 * @ingroup Protocol
 *
 * @date March 2018
 */
#include <string>
#include <vector>
#include "../../pluginLoader/include/I_protocolInterface.h"

#ifndef PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H
#define PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H

namespace hwProt
{
/*!
 * @brief HelloWorldProtocol
 *
 * declares the header that will be used to help generate and decode
 * the helloworldprotocol information
 */
class HelloWorldProtocol
    : public Protocol::I_protocolInterface
{
public:
    HelloWorldProtocol();
    ~HelloWorldProtocol() override = default;
    /*!
     * @brief Decodes the data returned from the target
     * @param payLoad The payload received from the target
     */
    void DecodeResult(Protocol::DataStruct& payLoad) override;
    /*!
     * @brief I don't think this does anything?
     * @return A pointer to a struct of data and sizes
     */
    std::shared_ptr<Protocol::DataStruct> GetDataToSend() override;
    /*!
     * @brief The final result of the returned data
     * @return The returned data
     */
    std::shared_ptr<Protocol::DataStruct> GetResult() override;
    /*!
     * @brief The result code returned/calculated
     * @return Result code
     */
    int GetResultCode() override;
    /*!
     * @brief Sets the protocols datapoints
     * @param testDP The datapoints we're using
     */
    void SetDataPoints(testAnalyser2::dataPoint testDP) override;
    /*! @brief Counts the number of instances */
    static int _numberOfInstances;

private:
    /*! @brief The datapoints we got from the test */
    testAnalyser2::dataPoint _testDP;
    /*! @brief Will store the received result as "raw" */
    Protocol::DataStruct _result;
    /*! @brief Stores the error code */
    int _resultCode;
    /*! vector that stores all our information */
    std::vector<std::string> _possibleResults;
    /*! @brief Bool that we can toggle to give us different things */
    bool helloOrGoodbye;
    /*! @brief Current instance ID */
    int _curInstance;
};
}

#endif //PROTOCOLDEVELOPER_HELLOWORLDPROTOCOL_H