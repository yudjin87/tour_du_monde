#ifndef CAROUSELBOOTLOADER_COMPONENTPROVIDERFIXTURE_H
#define CAROUSELBOOTLOADER_COMPONENTPROVIDERFIXTURE_H

#include <booting/CarouselBootloader.h>
#include <componentsystem/IComponentManager.h>

class CarouselBootloader_ComponentManagerFixture : public CarouselBootloader
{
public:
    IComponentManager &componentManager();

protected:
    void _configureComponentProvider();
};

#endif // CAROUSELBOOTLOADER_COMPONENTPROVIDERFIXTURE_H
