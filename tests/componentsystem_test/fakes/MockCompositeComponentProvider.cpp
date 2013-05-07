#include "MockCompositeComponentProvider.h"

#include <componentsystem/IComponent.h>

//------------------------------------------------------------------------------
MockCompositeComponentProvider::MockCompositeComponentProvider()
{
}

//------------------------------------------------------------------------------
MockCompositeComponentProvider::~MockCompositeComponentProvider()
{
    foreach(IComponentProvider *provider, m_providers)
        foreach(IComponent *component, provider->components())
            delete component;
}

//------------------------------------------------------------------------------
size_t MockCompositeComponentProvider::size() const
{
    return m_providers.size();
}

//------------------------------------------------------------------------------
