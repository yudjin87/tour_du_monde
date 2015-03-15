#include "TextLoggerTest.h"

#include <QtCore/QCoreApplication>

#include <QtTest/QtTest>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TextLoggerTest textLoggerTest;
    QTest::qExec(&textLoggerTest, argc, argv);

    return 0;
}


