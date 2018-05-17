#include "loggerObject.h"

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;

loggerObject::loggerObject()
{
    logging::add_file_log //inits the log
    (
        keywords::file_name = "../sample_%N.log",                                     /*< file name pattern >*/
        keywords::rotation_size = 10 * 1024 * 1024,                                   /*< rotate files every 10 MiB... >*/
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), /*< ...or at midnight >*/
        keywords::format = "[%TimeStamp%]: %Message%"                                 /*< log record format >*/
    );
}

loggerObject::~loggerObject()
{
    return;
}

void loggerObject::addLog()
{
    // The logger implicitly adds a source-specific attribute 'Severity'
    // of type 'severity_level' on construction
    src::severity_logger< severity_level > slg;
    
    BOOST_LOG_SEV(slg, normal) << "A regular message";
    BOOST_LOG_SEV(slg, warning) << "Something bad is going on but I can handle it";
    BOOST_LOG_SEV(slg, critical) << "Everything crumbles, shoot me now!";
}