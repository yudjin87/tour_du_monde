#pragma once
#include <carousel/componentsystem/BaseComponent.h>

class ComponentDefinition;

class MockChildComponent : public BaseComponent
{
    Q_OBJECT
public:
    explicit MockChildComponent(const QString &name = "MockChildComponent");
    MockChildComponent(const QString &name, int major_version, int minor_version, int build_version = 0, int revision_version = 0);

    const ParentDefinitions &parents() const;
    ParentDefinitions &parents();

protected:
    bool onStartup(IServiceLocator *serviceLocator);
    void onShutdown();

signals:
    void whenStarted(const QString &name);
    void whenShutdown(const QString &name);
};

