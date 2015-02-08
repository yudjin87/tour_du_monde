#ifndef CARTOBASETOOL_H
#define CARTOBASETOOL_H

#include <display/display_api.h>
#include <components/interactivity/ToolBase.h>

class DISPLAY_API CartoBaseTool : public ToolBase
{
public:
    CartoBaseTool(const QString &text, QActionGroup *actionGroup = nullptr);
    CartoBaseTool(const QIcon &icon, const QString &text, QActionGroup *actionGroup = nullptr);

    void initialize(IServiceLocator *serviceLocator) override;
    void onMouseMove(QMouseEvent *event) override;

private:
    IServiceLocator *m_serviceLocator;
};
#endif // CARTOBASETOOL_H
