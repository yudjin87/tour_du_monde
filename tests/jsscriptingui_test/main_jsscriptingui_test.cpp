#include "ScriptConsoleViewTest.h"

#include <carousel/logging/LoggerFacade.h>
#include <carousel/logging/TextLogger.h>

#include <QtTest/QTest>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextStream text(stdout);
    TextLogger log(text);
    LoggerFacade::installLoggerEngineCreator(&log);

    ScriptConsoleViewTest *scriptConsoleViewTest = new ScriptConsoleViewTest(QApplication::instance());
    scriptConsoleViewTest->test();

    return app.exec();
}


