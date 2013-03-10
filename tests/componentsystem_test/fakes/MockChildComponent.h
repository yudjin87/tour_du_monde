#ifndef MOCKCHILDCOMPONENT_H
#define MOCKCHILDCOMPONENT_H

#include <componentsystem/BaseComponent.h>

class ComponentDefinition;

class MockChildComponent : public BaseComponent
{
    Q_OBJECT
public:
    MockChildComponent();
    ~MockChildComponent();

    IComponentDefinition *definition() const;

    const QStringList &parents() const;
    QStringList &parents();
    void setName(const QString &i_name);

protected:
    bool _onStartup(QObject *ip_initData);
    void _onShutdown();

signals:
    void whenStarted(const QString &i_name);
    void whenShutdown(const QString &i_name);

private:
    ComponentDefinition *mp_def;
};

#endif // MOCKCHILDCOMPONENT_H
