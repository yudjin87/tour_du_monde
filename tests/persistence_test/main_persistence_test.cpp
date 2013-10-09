#include <carousel/logging/LoggerFacade.h>
#include <carousel/logging/NullLogger.h>

#include <QtTest/QTest>
#include <QtCore/QCoreApplication>

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    NullLogger log;
    LoggerFacade::installLoggerEngineCreator(&log);

    return 0;
}

//------------------------------------------------------------------------------
