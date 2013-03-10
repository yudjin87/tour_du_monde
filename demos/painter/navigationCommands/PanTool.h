#ifndef PANCOMMAND_H
#define PANCOMMAND_H

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
#endif // PANCOMMAND_H
