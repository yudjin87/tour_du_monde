#include "CarouselComponentConfigurationDelegateTest.h"
#include "CommandTest.h"
#include "CommandCatalogTest.h"
#include "DockWidgetCatalogTest.h"
#include "InputInterceptorTest.h"
#include "MenuCatalogTest.h"
#include "ToolBarCatalogTest.h"
#include "CarouselInteractionServiceTest.h"
#include "ToolBaseTest.h"
#include "DialogServiceTest.h"
#include "fakes/MockApplication.h"

#include <QtTest/QtTest>

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    MockApplication app(argc, argv);

    InputInterceptorTest inputInterceptorTest;
    QTest::qExec(&inputInterceptorTest, argc, argv);

    CommandTest commandTest;
    QTest::qExec(&commandTest, argc, argv);

    MenuCatalogTest menuCatalogTest;
    QTest::qExec(&menuCatalogTest, argc, argv);

    ToolBarCatalogTest toolBarCatalogTest;
    QTest::qExec(&toolBarCatalogTest, argc, argv);

    CommandCatalogTest commandCatalogTest;
    QTest::qExec(&commandCatalogTest, argc, argv);

    DockWidgetCatalogTest dockWidgetCatalogTest;
    QTest::qExec(&dockWidgetCatalogTest, argc, argv);

    CarouselComponentConfigurationDelegateTest carouselComponentConfigurationDelegateTest;
    QTest::qExec(&carouselComponentConfigurationDelegateTest, argc, argv);

    CarouselInteractionServiceTest carouselInteractionServiceTest;
    QTest::qExec(&carouselInteractionServiceTest, argc, argv);

    ToolBaseTest toolBaseTest;
    QTest::qExec(&toolBaseTest, argc, argv);

    DialogServiceTest dialogServiceTest;
    QTest::qExec(&dialogServiceTest, argc, argv);

    return 0;
}

//------------------------------------------------------------------------------

