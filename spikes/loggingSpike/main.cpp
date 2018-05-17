#include <boost/move/utility_core.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include "loggerObject.h"
#include <iostream>

#define BOOST_LOG_DYN_LINK 1

int main(int argc, char** argv)
{
  std::cout << "foo" << std::endl;
  loggerObject *log = new loggerObject;

  delete(log);

  return 0;
}