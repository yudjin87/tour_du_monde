#ifndef MOCKTOOL_H
#define MOCKTOOL_H

#include <interactivity/ITool.h>

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
    void initialize(QObject *ip_startUpData);
    QString name() const;

    // ITool:
    bool onContextMenu(QContextMenuEvent *ip_event);
    void onDoubleClick(QMouseEvent *ip_event);
    void onKeyDown(QKeyEvent *ip_event);
    void onKeyUp(QKeyEvent *ip_event);
    void onMouseDown(QMouseEvent *ip_event);
    void onMouseMove(QMouseEvent *ip_event);
    void onMouseUp(QMouseEvent *ip_event);

signals:
    void executingStopped();

public:
    // IOperation:
    bool executeCalled;
    bool stopExecutingCalled;
    bool initializeCalled;
    QObject *startUpData;

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
