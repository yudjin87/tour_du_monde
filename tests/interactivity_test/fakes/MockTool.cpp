#include "MockTool.h"

//------------------------------------------------------------------------------
MockTool::MockTool()
    : executeCalled(false)
    , stopExecutingCalled(false)
    , initializeCalled(false)
    , startUpData(nullptr)
    , contextMenuCalled(false)
    , doubleClickCalled(false)
    , keyDownCalled(false)
    , keyUpCalled(false)
    , mouseDownCalled(false)
    , mouseUpCalled(false)
    , mouseMoveCalled(false)
{
}

//------------------------------------------------------------------------------
void MockTool::execute()
{
    executeCalled = true;
}

//------------------------------------------------------------------------------
QString MockTool::category() const
{
    static QString toolCategory = "Mocking tool";
    return toolCategory;
}

//------------------------------------------------------------------------------
void MockTool::stopExecuting()
{
    stopExecutingCalled = true;
}

//------------------------------------------------------------------------------
void MockTool::initialize(QObject *startUpData)
{
    initializeCalled = true;
    startUpData = startUpData;
}

//------------------------------------------------------------------------------
QString MockTool::name() const
{
    static QString toolName = "Mocking tool";
    return toolName;
}

//------------------------------------------------------------------------------
bool MockTool::onContextMenu(QContextMenuEvent *)
{
    contextMenuCalled = true;
    return true;
}

//------------------------------------------------------------------------------
void MockTool::onDoubleClick(QMouseEvent *)
{
    doubleClickCalled = true;
}

//------------------------------------------------------------------------------
void MockTool::onKeyDown(QKeyEvent *)
{
    keyDownCalled = true;
}

//------------------------------------------------------------------------------
void MockTool::onKeyUp(QKeyEvent *)
{
    keyUpCalled = true;
}

//------------------------------------------------------------------------------
void MockTool::onMouseDown(QMouseEvent *)
{
    mouseDownCalled = true;
}

//------------------------------------------------------------------------------
void MockTool::onMouseMove(QMouseEvent *)
{
    mouseMoveCalled = true;
}

//------------------------------------------------------------------------------
void MockTool::onMouseUp(QMouseEvent *)
{
    mouseUpCalled = true;
}

//------------------------------------------------------------------------------
