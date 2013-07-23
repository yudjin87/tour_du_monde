#include "ServiceLocatorWrapperTest.h"
#include "ScriptEngineTest.h"

#include <QtCore/QCoreApplication>
#include <QtTest/QtTest>

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Q_UNUSED(app)

    ServiceLocatorWrapperTest serviceLocatorWrapperTest;
    QTest::qExec(&serviceLocatorWrapperTest, argc, argv);

    ScriptEngineTest scriptEngineTest;
    QTest::qExec(&scriptEngineTest, argc, argv);

    return 0;
}

//------------------------------------------------------------------------------

