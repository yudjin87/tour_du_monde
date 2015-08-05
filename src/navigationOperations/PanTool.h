#pragma once
#include <components/interactivity/ToolBase.h>

class PanTool : public ToolBase
{
public:
    PanTool();

    void execute() override;
    void initialize(IServiceLocator *serviceLocator) override;
    bool onMouseDown(QMouseEvent *event) override;
    bool onMouseMove(QMouseEvent *event) override;
    bool onMouseUp(QMouseEvent *event) override;
    void stopExecuting() override;

private:
    IServiceLocator *m_serviceLocator;
    bool m_tracked;
};
