#include "CarouselBootloader_ComponentManagerFixture.h"

#include <componentsystem/BaseComponent.h>
#include <componentsystem/IComponentProvider.h>

class ComponentStub : public BaseComponent
{
public:
    ComponentStub(const QString &i_name)
        : BaseComponent(i_name)
    {
    }
};

//------------------------------------------------------------------------------
IComponentManager &CarouselBootloader_ComponentManagerFixture::componentManager()
{
    return *m_componentManager;
}

//------------------------------------------------------------------------------
void CarouselBootloader_ComponentManagerFixture::_configureComponentProvider()
{
    m_componentProvider->registerComponent(new ComponentStub("ComponentStubA"));
    m_componentProvider->registerComponent(new ComponentStub("ComponentStubB"));
}

//------------------------------------------------------------------------------
