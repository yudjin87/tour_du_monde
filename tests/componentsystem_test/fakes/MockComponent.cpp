#include "MockComponent.h"

#include <carousel/componentsystem/ComponentDefinition.h>

MockComponent::MockComponent(const QString &name, bool isBuiltIn)
    : BaseComponent(new ComponentDefinition(name, isBuiltIn))
    , m_serviceLocator(nullptr)
    , m_returnValue(true)
    , m_onStartupCalled(false)
    , m_onShutdownCalled(false)
    , m_registrator(nullptr)
{
    setAvailability(IComponent::Enabled);
}

MockComponent::MockComponent(const QString &name, int major_version, int minor_version, int build_version, int revision_version)
    : BaseComponent(new ComponentDefinition(name, false))
    , m_serviceLocator(nullptr)
    , m_returnValue(true)
    , m_onStartupCalled(false)
    , m_onShutdownCalled(false)
    , m_registrator(nullptr)
{
    setAvailability(IComponent::Enabled);
    setVersion(major_version, minor_version, build_version, revision_version);
}

MockComponent::~MockComponent()
{
}

IServiceLocator *MockComponent::data() const
{
    return m_serviceLocator;
}

void MockComponent::setRegistrator(QList<MockComponent *> *registrator)
{
    m_registrator = registrator;
}

bool MockComponent::onStartup(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
    emit whenStarted(name());
    m_onStartupCalled = true;
    return m_returnValue;
}

void MockComponent::onShutdown(IServiceLocator *serviceLocator)
{
    Q_UNUSED(serviceLocator)
    if (m_registrator != nullptr)
        m_registrator->push_back(this);

    m_onShutdownCalled = true;
    emit whenShutdown(name());
}


