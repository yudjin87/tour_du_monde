#include "MockCompositeComponentProvider.h"

#include <componentsystem/IComponent.h>

//------------------------------------------------------------------------------
MockCompositeComponentProvider::MockCompositeComponentProvider()
{
}

//------------------------------------------------------------------------------
MockCompositeComponentProvider::~MockCompositeComponentProvider()
{
    foreach(IComponentProvider *p_provider, m_providers)
        foreach(IComponent *p_component, p_provider->components())
            delete p_component;
}

//------------------------------------------------------------------------------
size_t MockCompositeComponentProvider::size() const
{
    return m_providers.size();
}

//------------------------------------------------------------------------------
