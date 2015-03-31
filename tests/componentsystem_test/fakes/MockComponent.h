#pragma once
#include <carousel/componentsystem/BaseComponent.h>

class MockComponent : public BaseComponent
{
   Q_OBJECT
public:
    explicit MockComponent(const QString &name = "MockComponent", bool isBuiltIn = false);
    MockComponent(const QString &name, int major_version, int minor_version, int build_version = 0, int revision_version = 0);
    ~MockComponent();

    IServiceLocator *data() const;

    void setRegistrator(QList<MockComponent *> *registrator);

protected:
    bool onStartup(IServiceLocator *serviceLocator);
    void onShutdown(IServiceLocator *serviceLocator);

signals:
    void whenStarted(const QString &name);
    void whenShutdown(const QString &name);

public:
    IServiceLocator *m_serviceLocator;
    bool m_returnValue;
    bool m_onStartupCalled;
    bool m_onShutdownCalled;
    QList<MockComponent *> *m_registrator;
};

