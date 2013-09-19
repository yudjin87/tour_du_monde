#include "MockCompositeComponentProvider.h"

#include <carousel/componentsystem/IComponent.h>

//------------------------------------------------------------------------------
MockCompositeComponentProvider::MockCompositeComponentProvider()
{
}

//------------------------------------------------------------------------------
MockCompositeComponentProvider::~MockCompositeComponentProvider()
{
    for (IComponentProvider *provider : m_providers)
        for (IComponent *component : provider->components())
            delete component;
}

//------------------------------------------------------------------------------
size_t MockCompositeComponentProvider::size() const
{
    return m_providers.size();
}

//------------------------------------------------------------------------------
