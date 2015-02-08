#ifndef PANTOOL_H
#define PANTOOL_H

#include <display/CartoBaseTool.h>

class PanTool : public CartoBaseTool
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
#endif // PANTOOL_H
