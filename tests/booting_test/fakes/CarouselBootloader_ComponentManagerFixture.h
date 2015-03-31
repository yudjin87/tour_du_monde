#pragma once
#include <carousel/booting/CarouselBootloader.h>
#include <carousel/componentsystem/IComponentManager.h>

class CarouselBootloader_ComponentManagerFixture : public CarouselBootloader
{
public:
    IComponentManager &componentManager();

protected:
    void configureComponentProvider();
};

