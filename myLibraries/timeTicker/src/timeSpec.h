/*!
 * @brief Decalarations for the higher precision timeSpec functions
 *
 * @author hmarcks
 *
 * @addtogroup TimeTicker
 *
 * @date 18/12/18
 */

#ifndef PROTOCOLDEVELOPER_TIMESPEC_H
#define PROTOCOLDEVELOPER_TIMESPEC_H

#include <cstdint>

namespace TimeTicker
{

class TimeSpec
{
public:
    TimeSpec();
    ~TimeSpec() = default;
    int getTimeSpecSubtract(const struct timespec* first_p
                            , const struct timespec* second_p
                            , struct timespec* result_p);
    void getTimeSpecAdd(const struct timespec* first_p
                        , const struct timespec* second_p
                        , struct timespec* result_p);
    int64_t getTimeSpecDiff(const struct timespec* timeA_p
                            , const struct timespec* timeB_p);
    int64_t getTimeSpecDiffNS(const struct timespec* timeA_p
                              , const struct timespec* timeB_p);
    int64_t getTimeSpecDiffUS(const struct timespec* timeA_p
                              , const struct timespec* timeB_p);
    int64_t getTimeSpecDiffMS(const struct timespec* timeA_p
                              , const struct timespec* timeB_p);
    int64_t getTimeSpecDiffS(const struct timespec* timeA_p
                             , const struct timespec* timeB_p);
private:
};
}

#endif /* PROTOCOLDEVELOPER_TIMESPEC_H */
