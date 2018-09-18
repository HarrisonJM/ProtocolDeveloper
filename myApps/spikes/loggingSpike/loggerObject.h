#include "boost/log/utility/setup.hpp"
#include "boost/log/core/core.hpp"
#include "boost/log/core.hpp"
#include "boost/log/trivial.hpp"
#include "boost/log/expressions.hpp"
#include "boost/log/sinks/text_file_backend.hpp"
#include "boost/log/utility/setup/file.hpp"
#include "boost/log/utility/setup/common_attributes.hpp"
#include "boost/log/sources/record_ostream.hpp"

#include "boost/log/sources/severity_logger.hpp"
#include "boost/log/sources/severity_feature.hpp"

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

//BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)

// We define our own severity levels
enum severity_level
{
    normal,
    notification,
    warning,
    error,
    critical
};

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::severity_logger_mt< >)

class loggerObject
{
public:
  loggerObject();
  ~loggerObject();
  void addLog();
};