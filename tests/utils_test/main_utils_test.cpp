#include "ServiceLocatorTest.h"
#include "ObservableListTest.h"

#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    ServiceLocatorTest serviceLocatorTest;
    QTest::qExec(&serviceLocatorTest, argc, argv);

    ObservableListTest observableListTest;
    QTest::qExec(&observableListTest, argc, argv);

    return 0;
}

//------------------------------------------------------------------------------

