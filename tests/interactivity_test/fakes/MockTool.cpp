#include "MockTool.h"

MockTool::MockTool()
    : executeCalled(false)
    , stopExecutingCalled(false)
    , initializeCalled(false)
    , serviceLocator(nullptr)
    , contextMenuCalled(false)
    , doubleClickCalled(false)
    , keyDownCalled(false)
    , keyUpCalled(false)
    , mouseDownCalled(false)
    , mouseUpCalled(false)
    , mouseMoveCalled(false)
{
}

void MockTool::execute()
{
    executeCalled = true;
}

QString MockTool::category() const
{
    static QString toolCategory = "Mocking tool";
    return toolCategory;
}

void MockTool::stopExecuting()
{
    stopExecutingCalled = true;
}

void MockTool::initialize(IServiceLocator *serviceLocator)
{
    initializeCalled = true;
    serviceLocator = serviceLocator;
}

QString MockTool::name() const
{
    static QString toolName = "Mocking tool";
    return toolName;
}

bool MockTool::onContextMenu(QContextMenuEvent *)
{
    contextMenuCalled = true;
    return true;
}

bool MockTool::onDoubleClick(QMouseEvent *)
{
    doubleClickCalled = true;
    return true;
}

bool MockTool::onKeyDown(QKeyEvent *)
{
    keyDownCalled = true;
    return true;
}

bool MockTool::onKeyUp(QKeyEvent *)
{
    keyUpCalled = true;
    return true;
}

bool MockTool::onMouseDown(QMouseEvent *)
{
    mouseDownCalled = true;
    return true;
}

bool MockTool::onMouseMove(QMouseEvent *)
{
    mouseMoveCalled = true;
    return true;
}

bool MockTool::onMouseUp(QMouseEvent *)
{
    mouseUpCalled = true;
    return true;
}

