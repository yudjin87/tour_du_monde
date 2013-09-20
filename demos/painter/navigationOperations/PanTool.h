#ifndef PANOPERATION_H
#define PANOPERATION_H

#include <components/interactivity/ToolBase.h>

class PanTool : public ToolBase
{
public:
    PanTool();

    void execute() override;
    void initialize(IServiceLocator *serviceLocator) override;
    void onMouseDown(QMouseEvent *event) override;
    void onMouseMove(QMouseEvent *event) override;
    void onMouseUp(QMouseEvent *event) override;
    void stopExecuting() override;

private:
    IServiceLocator *m_serviceLocator;
    bool m_tracked;
};
#endif // PANOPERATION_H
