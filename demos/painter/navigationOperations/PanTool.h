#ifndef PANOPERATION_H
#define PANOPERATION_H

#include <components/interactivity/ToolBase.h>

class PanTool : public ToolBase
{
public:
    PanTool();

    void execute();
    void initialize(IServiceLocator *serviceLocator);
    void onMouseDown(QMouseEvent *event);
    void onMouseMove(QMouseEvent *event);
    void onMouseUp(QMouseEvent *event);
    void stopExecuting();

private:
    IServiceLocator *m_serviceLocator;
    bool m_tracked;
};
#endif // PANOPERATION_H
