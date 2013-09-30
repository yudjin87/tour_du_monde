#include "CarouselComponentConfigurationDelegateTest.h"
#include "OperationTest.h"
#include "OperationCatalogTest.h"
#include "DockWidgetCatalogTest.h"
#include "InputDispatcherTest.h"
#include "MenuCatalogTest.h"
#include "ToolBarCatalogTest.h"
#include "CarouselInteractionServiceTest.h"
#include "ToolBaseTest.h"
#include "DialogServiceTest.h"

#include <carousel/logging/LoggerFacade.h>
#include <carousel/logging/NullLogger.h>

#include <QtTest/QtTest>
#include <QtWidgets/QApplication>

//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    NullLogger log;
    LoggerFacade::installLoggerEngineCreator(&log);

    InputDispatcherTest indispatcherst;
    QTest::qExec(&indispatcherst, argc, argv);

    OperationTest operationTest;
    QTest::qExec(&operationTest, argc, argv);

    MenuCatalogTest menuCatalogTest;
    QTest::qExec(&menuCatalogTest, argc, argv);

    ToolBarCatalogTest toolBarCatalogTest;
    QTest::qExec(&toolBarCatalogTest, argc, argv);

    OperationCatalogTest operationCatalogTest;
    QTest::qExec(&operationCatalogTest, argc, argv);

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

