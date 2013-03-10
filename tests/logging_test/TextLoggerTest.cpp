#include "TextLoggerTest.h"
#include <logging/TextLogger.h>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
TextLoggerTest::TextLoggerTest()
{
}

//------------------------------------------------------------------------------
void TextLoggerTest::writeToStream_data()
{
    QTest::addColumn<QString>("message");
    QTest::addColumn<int>("category");
    QTest::addColumn<int>("priority");
    QTest::addColumn<QString>("categoryStr");
    QTest::addColumn<QString>("priorityStr");

    QTest::newRow("Test 0") << "Test 0" << (int)ILogger::Debug   << (int)ILogger::None   << "Debug"   << "None";
    QTest::newRow("Test 1") << "Test 1" << (int)ILogger::Info    << (int)ILogger::Low    << "Info"    << "Low";
    QTest::newRow("Test 2") << "Test 2" << (int)ILogger::Warning << (int)ILogger::Medium << "Warning" << "Medium";
    QTest::newRow("Test 3") << "Test 3" << (int)ILogger::Error   << (int)ILogger::High   << "Error"   << "High";

}

//------------------------------------------------------------------------------
void TextLoggerTest::writeToStream()
{
    QFETCH(QString, message);
    QFETCH(int, category);
    QFETCH(int, priority);
    QFETCH(QString, categoryStr);
    QFETCH(QString, priorityStr);

    QString log;
    QTextStream out(&log);
    TextLogger logger(out);

    logger.log(message, (ILogger::Category)category, (ILogger::Priority)priority);

    QVERIFY(log.contains(message));
    QVERIFY(log.contains(categoryStr));
    QVERIFY(log.contains(priorityStr));
}

//------------------------------------------------------------------------------
