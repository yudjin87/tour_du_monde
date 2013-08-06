#include "ServiceLocatorWrapperTest.h"
#include "ScriptEngineTest.h"
#include "ScriptConsoleTest.h"
#include "ScriptingServiceTest.h"
#include "ScriptUnitTest.h"
#include "ScriptManagerTest.h"
#include "CarouselEngineConfigurationDelegateTest.h"

#include "ScriptConsoleViewTest.h"

#include <carousel/logging/NullLogger.h>
#include <carousel/logging/TextLogger.h>

#include <QtCore/QStringList>
#include <QtTest/QTest>
#include <QtWidgets/QApplication>

//------------------------------------------------------------------------------
void runGuiManualTests(QStringList arguments);
void runUnitTests(int argc, char *argv[]);

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (app.arguments().contains("-g")) {
        QTextStream text(stdout);
        TextLogger log(text);
        LoggerFacade::installLoggerEngine(&log);
        runGuiManualTests(app.arguments());
        return app.exec();
    } else {
        NullLogger log;
        LoggerFacade::installLoggerEngine(&log);
        runUnitTests(argc, argv);
        return 0;
    }
}

//------------------------------------------------------------------------------
void runUnitTests(int argc, char *argv[])
{
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

    ScriptManagerTest scriptManagerTest;
    QTest::qExec(&scriptManagerTest, argc, argv);

    CarouselEngineConfigurationDelegateTest carouselEngineConfigurationDelegateTest;
    QTest::qExec(&carouselEngineConfigurationDelegateTest, argc, argv);
}

//------------------------------------------------------------------------------
void runGuiManualTests(QStringList arguments)
{
    if (arguments.contains("ScriptConsoleViewTest")) {
        ScriptConsoleViewTest *scriptConsoleViewTest = new ScriptConsoleViewTest(QApplication::instance());
        scriptConsoleViewTest->test();
    }
}

//------------------------------------------------------------------------------

