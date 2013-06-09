#ifndef CAROUSELBOOTLOADER_COMPONENTPROVIDERFIXTURE_H
#define CAROUSELBOOTLOADER_COMPONENTPROVIDERFIXTURE_H

#include <carousel/booting/CarouselBootloader.h>
#include <carousel/componentsystem/IComponentManager.h>

class CarouselBootloader_ComponentManagerFixture : public CarouselBootloader
{
public:
    IComponentManager &componentManager();

protected:
    void configureComponentProvider();
};

#endif // CAROUSELBOOTLOADER_COMPONENTPROVIDERFIXTURE_H
