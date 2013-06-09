#include "CarouselBootloader_ComponentManagerFixture.h"

#include <carousel/componentsystem/BaseComponent.h>
#include <carousel/componentsystem/IComponentProvider.h>

class ComponentStub : public BaseComponent
{
public:
    ComponentStub(const QString &name)
        : BaseComponent(name)
    {
    }
};

//------------------------------------------------------------------------------
IComponentManager &CarouselBootloader_ComponentManagerFixture::componentManager()
{
    return *m_componentManager;
}

//------------------------------------------------------------------------------
void CarouselBootloader_ComponentManagerFixture::configureComponentProvider()
{
    m_componentProvider->registerComponent(new ComponentStub("ComponentStubA"));
    m_componentProvider->registerComponent(new ComponentStub("ComponentStubB"));
}

//------------------------------------------------------------------------------
