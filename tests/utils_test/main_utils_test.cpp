#include "ServiceLocatorTest.h"
#include "ObservableListTest.h"

#include <carousel/logging/LoggerFacade.h>
#include <carousel/logging/NullLogger.h>

#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    NullLogger log;
    LoggerFacade::installLoggerEngineCreator(&log);

    ServiceLocatorTest serviceLocatorTest;
    QTest::qExec(&serviceLocatorTest, argc, argv);

    ObservableListTest observableListTest;
    QTest::qExec(&observableListTest, argc, argv);

    return 0;
}

//------------------------------------------------------------------------------

