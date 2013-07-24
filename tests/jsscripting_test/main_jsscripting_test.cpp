#include "ServiceLocatorWrapperTest.h"
#include "ScriptEngineTest.h"
#include "ScriptConsoleTest.h"

#include "ScriptConsoleViewTest.h"

#include <carousel/logging/NullLogger.h>

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

    NullLogger log;
    LoggerFacade::installLoggerEngine(&log);

    if (app.arguments().contains("-g")) {
        runGuiManualTests(app.arguments());
        return app.exec();
    } else {
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
}

//------------------------------------------------------------------------------
void runGuiManualTests(QStringList arguments)
{
    Q_UNUSED(arguments)

    ScriptConsoleViewTest *scriptConsoleViewTest = new ScriptConsoleViewTest(QApplication::instance());
    scriptConsoleViewTest->test();
}

//------------------------------------------------------------------------------

