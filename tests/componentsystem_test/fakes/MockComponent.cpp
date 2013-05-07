#include "MockComponent.h"

#include <componentsystem/ComponentDefinition.h>

//------------------------------------------------------------------------------
MockComponent::MockComponent(const QString &i_name, bool isBuiltIn)
    : BaseComponent(new ComponentDefinition(i_name, isBuiltIn))
    , m_initData(nullptr)
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
QObject *MockComponent::data() const
{
    return m_initData;
}

//------------------------------------------------------------------------------
void MockComponent::setRegistrator(QList<MockComponent *> *registrator)
{
    m_registrator = registrator;
}

//------------------------------------------------------------------------------
bool MockComponent::_onStartup(QObject *initData)
{
    m_initData = initData;
    emit whenStarted(name());
    return m_returnValue;
}

//------------------------------------------------------------------------------
void MockComponent::_onShutdown()
{
    if (m_registrator != nullptr)
        m_registrator->push_back(this);

    emit whenShutdown(name());
}


//------------------------------------------------------------------------------
