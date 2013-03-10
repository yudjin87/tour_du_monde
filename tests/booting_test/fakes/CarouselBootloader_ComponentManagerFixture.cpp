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
    return *mp_componentManager;
}

//------------------------------------------------------------------------------
void CarouselBootloader_ComponentManagerFixture::_configureComponentProvider()
{
    mp_componentProvider->registerComponent(new ComponentStub("ComponentStubA"));
    mp_componentProvider->registerComponent(new ComponentStub("ComponentStubB"));
}

//------------------------------------------------------------------------------
