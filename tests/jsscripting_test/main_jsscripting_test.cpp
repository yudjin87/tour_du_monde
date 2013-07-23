#include "ServiceLocatorWrapperTest.h"
#include "ScriptEngineTest.h"

#include "ScriptConsoleViewTest.h"

#include <QtCore/QStringList>
#include <QtTest/QTest>
#include <QtWidgets/QApplication>

//------------------------------------------------------------------------------
void runGuiManualTests(QStringList arguments);
void runUnitTests();

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if (app.arguments().contains("-g")) {
        runGuiManualTests(app.arguments());
        return app.exec();
    } else {
        runUnitTests();
        return 0;
    }
}

//------------------------------------------------------------------------------
void runUnitTests()
{
    ServiceLocatorWrapperTest serviceLocatorWrapperTest;
    QTest::qExec(&serviceLocatorWrapperTest, argc, argv);

    ScriptEngineTest scriptEngineTest;
    QTest::qExec(&scriptEngineTest, argc, argv);
}

//------------------------------------------------------------------------------
void runGuiManualTests(QStringList arguments)
{
    Q_UNUSED(arguments)

    ScriptConsoleViewTest *scriptConsoleViewTest = new ScriptConsoleViewTest(QApplication::instance());
    scriptConsoleViewTest->test();
}

//------------------------------------------------------------------------------

