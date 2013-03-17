#ifndef MOCKCHILDCOMPONENT_H
#define MOCKCHILDCOMPONENT_H

#include <componentsystem/BaseComponent.h>

class ComponentDefinition;

class MockChildComponent : public BaseComponent
{
    Q_OBJECT
public:
    MockChildComponent(const QString &i_name = "MockChildComponent");

    const QStringList &parents() const;
    QStringList &parents();

protected:
    bool _onStartup(QObject *ip_initData);
    void _onShutdown();

signals:
    void whenStarted(const QString &i_name);
    void whenShutdown(const QString &i_name);
};

#endif // MOCKCHILDCOMPONENT_H
