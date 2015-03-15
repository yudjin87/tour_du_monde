#include "ServiceLocatorWrapperTest.h"
#include "ScriptEngineTest.h"
#include "ScriptConsoleTest.h"
#include "ScriptingServiceTest.h"
#include "ScriptUnitTest.h"
#include "ScriptCollectionTest.h"
#include "CarouselScriptEngineConfigurationDelegateTest.h"
#include "SimpleCompleterTest.h"

#include <carousel/logging/LoggerFacade.h>
#include <carousel/logging/NullLogger.h>

#include <QtTest/QTest>
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    NullLogger log;
    LoggerFacade::installLoggerEngineCreator(&log);

    ServiceLocatorWrapperTest serviceLocatorWrapperTest;
    QTest::qExec(&serviceLocatorWrapperTest, argc, argv);

    ScriptEngineTest scriptEngineTest;
    QTest::qExec(&scriptEngineTest, argc, argv);

    ScriptConsoleTest scriptConsoleTest;
    QTest::qExec(&scriptConsoleTest, argc, argv);

    ScriptingServiceTest scriptServiceTest;
    QTest::qExec(&scriptServiceTest, argc, argv);

    ScriptUnitTest scriptUnitTest;
    QTest::qExec(&scriptUnitTest, argc, argv);

    ScriptCollectionTest scriptManagerTest;
    QTest::qExec(&scriptManagerTest, argc, argv);

    CarouselScriptEngineConfigurationDelegateTest carouselScriptEngineConfigurationDelegateTest;
    QTest::qExec(&carouselScriptEngineConfigurationDelegateTest, argc, argv);

    SimpleCompleterTest simpleCompleterTest;
    QTest::qExec(&simpleCompleterTest, argc, argv);

    return 0;
}

