/*!
 * @brief Declarations for Turning the time into an XML format
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */


#ifndef PROTOCOLDEVELOPER_XMLTIME_H
#define PROTOCOLDEVELOPER_XMLTIME_H

namespace timeTicker
{

/*!
 * @brief XML string lengths
 * @{
 */
#define TT_XML_TS_DATE_START 0
#define TT_XML_TS_TIME_START 11
#define TT_XML_TS_SEPARATOR 10
#define TT_XML_TS_DATE_LEN 10
#define TT_XML_TS_TIME_LEN 14
#define TT_XML_TS_DATETIME_LEN 25
/*!@}*/

class XMLTime
{
public:
    XMLTime();
    ~XMLTime();
    char* getXMLTimestamp(time_t t
                          , int components);
private:
};

} /* timeTicker */

#endif /*PROTOCOLDEVELOPER_XMLTIME_H*/
