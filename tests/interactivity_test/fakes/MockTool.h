#ifndef MOCKTOOL_H
#define MOCKTOOL_H

#include <components/interactivity/ITool.h>

#include <QtCore/QObject>

class MockTool : public QObject, public ITool
{
    Q_OBJECT
public:
    MockTool();

    // IOperation:
    void execute();
    QString category() const;
    void stopExecuting();
    void initialize(IServiceLocator *serviceLocator);
    QString name() const;

    // ITool:
    bool onContextMenu(QContextMenuEvent *event);
    bool onDoubleClick(QMouseEvent *event);
    bool onKeyDown(QKeyEvent *event);
    bool onKeyUp(QKeyEvent *event);
    bool onMouseDown(QMouseEvent *event);
    bool onMouseMove(QMouseEvent *event);
    bool onMouseUp(QMouseEvent *event);

signals:
    void executingStopped();

public:
    // IOperation:
    bool executeCalled;
    bool stopExecutingCalled;
    bool initializeCalled;
    IServiceLocator *serviceLocator;

    // ITool:
    bool contextMenuCalled;
    bool doubleClickCalled;
    bool keyDownCalled;
    bool keyUpCalled;
    bool mouseDownCalled;
    bool mouseUpCalled;
    bool mouseMoveCalled;
};

#endif // MOCKTOOL_H
