#ifndef MOCKCHILDCOMPONENT_H
#define MOCKCHILDCOMPONENT_H

#include <componentsystem/BaseComponent.h>

class ComponentDefinition;

class MockChildComponent : public BaseComponent
{
    Q_OBJECT
public:
    MockChildComponent(const QString &name = "MockChildComponent");

    const QStringList &parents() const;
    QStringList &parents();

protected:
    bool _onStartup(QObject *initData);
    void _onShutdown();

signals:
    void whenStarted(const QString &name);
    void whenShutdown(const QString &name);
};

#endif // MOCKCHILDCOMPONENT_H
