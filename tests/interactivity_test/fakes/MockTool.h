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
    void initialize(QObject *startUpData);
    QString name() const;

    // ITool:
    bool onContextMenu(QContextMenuEvent *event);
    void onDoubleClick(QMouseEvent *event);
    void onKeyDown(QKeyEvent *event);
    void onKeyUp(QKeyEvent *event);
    void onMouseDown(QMouseEvent *event);
    void onMouseMove(QMouseEvent *event);
    void onMouseUp(QMouseEvent *event);

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
