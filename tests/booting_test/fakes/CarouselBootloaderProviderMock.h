#ifndef CAROUSELBOOTLOADERPROVIDERMOCK_H
#define CAROUSELBOOTLOADERPROVIDERMOCK_H

#include <carousel/booting/CarouselBootloader.h>
#include <carousel/componentsystem/ComponentProvider.h>

class ComponentProviderMock : public ComponentProvider
{
public:
    ComponentProviderMock();

public:
    bool initialiseCalled() const;

protected:
    virtual bool onInitialize();

private:
    bool m_initialiseCalled;
};

//------------------------------------------------------------------------------
class CarouselBootloaderProviderMock : public CarouselBootloader
{
public:
    CarouselBootloaderProviderMock();

public:
    const ComponentProviderMock & componentProvider() const;

protected:
    IComponentProvider *createComponentProvider();

private:
    ComponentProviderMock* m_componentProviderMock;
};

#endif // CAROUSELBOOTLOADERPROVIDERMOCK_H
