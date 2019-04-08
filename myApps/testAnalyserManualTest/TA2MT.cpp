/*!
 * @brief Functions as a simple manual verification of the testanalyser library soI can mvoe on
 *
 * @author hmarcks
 *
 * @addtogroup DUTTY
 *
 * @date 12/01/19
 */

#include <testAnalyser2/testAnalyser2.h>
#include <iostream>

int main()
{
//    std::string xmlLocation = "/home/hmarcks/src/ProtocolDeveloper/myLibraries/testAnalyser2/broken.xml";
    std::string xmlLocation = "aaaa";
    try
    {
        testAnalyser2::TestAnalyser2 TA2(xmlLocation
                                         , 0);
        TA2.startAnalysis();
        testAnalyser2::TestFile& TF = TA2.GetTestFile();
    }
    catch (std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}