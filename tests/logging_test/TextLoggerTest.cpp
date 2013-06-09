#include "TextLoggerTest.h"
#include <carousel/logging/TextLogger.h>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
TextLoggerTest::TextLoggerTest()
{
}

//------------------------------------------------------------------------------
void TextLoggerTest::writeToStream()
{
    QString log;
    QTextStream out(&log);

    TextLogger logger(out);

    QString message = "Hello, world!";
    logger.i(message);

    QVERIFY(log.contains(message));
    QVERIFY(log.contains("Info"));
}

//------------------------------------------------------------------------------
