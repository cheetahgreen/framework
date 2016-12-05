#include "fw/Framework.hpp"
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

namespace fw
{


void initialize(int argc, const char *argv[])
{
    const char *frameworkLoggerName = "framework";
    START_EASYLOGGINGPP(argc, argv);
    el::Loggers::getLogger(frameworkLoggerName);
    CLOG(INFO, frameworkLoggerName) << "Framework initialized.";
}

}
