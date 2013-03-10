#include "BaseBootloaderTest.h"
#include "CarouselBootloaderTest.h"

#include <QtGui/QApplication>

#include <QtTest/QtTest>

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    BaseBootloaderTest baseBootloaderTest;
    QTest::qExec(&baseBootloaderTest, argc, argv);

    CarouselBootloaderTest carouselBootloaderTest;
    QTest::qExec(&carouselBootloaderTest, argc, argv);

    return 0;
}

//------------------------------------------------------------------------------

