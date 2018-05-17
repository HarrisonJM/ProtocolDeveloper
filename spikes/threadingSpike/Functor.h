#include <iostream>
#include <boost/thread.hpp>
#include <boost/date_time.hpp>

class Worker
{
public: 

  Worker(unsigned N, float guess, unsigned iter);

  void operator()();

private:

  unsigned    m_Number;
  float       m_Guess;
  unsigned    m_Iterations;
};