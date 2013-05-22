#include "MockComponent.h"

#include <componentsystem/ComponentDefinition.h>

//------------------------------------------------------------------------------
MockComponent::MockComponent(const QString &name, bool isBuiltIn)
    : BaseComponent(new ComponentDefinition(name, isBuiltIn))
    , m_serviceLocator(nullptr)
    , m_returnValue(true)
    , m_registrator(nullptr)
{
    setAvailability(IComponent::Enabled);
}

//------------------------------------------------------------------------------
MockComponent::~MockComponent()
{
}

//------------------------------------------------------------------------------
IServiceLocator *MockComponent::data() const
{
    return m_serviceLocator;
}

//------------------------------------------------------------------------------
void MockComponent::setRegistrator(QList<MockComponent *> *registrator)
{
    m_registrator = registrator;
}

//------------------------------------------------------------------------------
bool MockComponent::onStartup(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
    emit whenStarted(name());
    return m_returnValue;
}

//------------------------------------------------------------------------------
void MockComponent::onShutdown()
{
    if (m_registrator != nullptr)
        m_registrator->push_back(this);

    emit whenShutdown(name());
}


//------------------------------------------------------------------------------
