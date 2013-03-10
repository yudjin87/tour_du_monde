#include "CarouselBootloaderProviderMock.h"

//------------------------------------------------------------------------------
ComponentProviderMock::ComponentProviderMock()
    : m_initialiseCalled(false)
{
}

//------------------------------------------------------------------------------
bool ComponentProviderMock::initialiseCalled() const
{
    return m_initialiseCalled;
}

//------------------------------------------------------------------------------
bool ComponentProviderMock::_initialize()
{
    m_initialiseCalled = true;
    return true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
CarouselBootloaderProviderMock::CarouselBootloaderProviderMock()
 : mp_componentProviderMock(nullptr)
{
}

const ComponentProviderMock &CarouselBootloaderProviderMock::componentProvider() const
{
    return *mp_componentProviderMock;
}

//------------------------------------------------------------------------------
IComponentProvider *CarouselBootloaderProviderMock::_createComponentProvider()
{
    if (mp_componentProviderMock == nullptr)
        mp_componentProviderMock = new ComponentProviderMock();

    return mp_componentProviderMock;
}

//------------------------------------------------------------------------------

