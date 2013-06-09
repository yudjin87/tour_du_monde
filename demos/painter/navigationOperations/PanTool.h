#ifndef PANOPERATION_H
#define PANOPERATION_H

#include <components/interactivity/ToolBase.h>

class PanTool : public ToolBase
{
public:
    PanTool();

    void execute();
    void initialize(IServiceLocator *serviceLocator);
    void onMouseMove(QMouseEvent *ip_event);
    void stopExecuting();

private:
    IServiceLocator *m_serviceLocator;
};
#endif // PANOPERATION_H
