#ifndef PANOPERATION_H
#define PANOPERATION_H

#include <interactivity/ToolBase.h>

class AbstractApplication;

class PanTool : public ToolBase
{
public:
    PanTool();

    void execute();
    void initialize(QObject *ip_startUpData);
    void onMouseMove(QMouseEvent *ip_event);
    void stopExecuting();

private:
    AbstractApplication *m_app;
};
#endif // PANOPERATION_H
