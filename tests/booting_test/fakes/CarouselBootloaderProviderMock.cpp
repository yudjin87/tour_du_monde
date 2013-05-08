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
bool ComponentProviderMock::onInitialize()
{
    m_initialiseCalled = true;
    return true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
CarouselBootloaderProviderMock::CarouselBootloaderProviderMock()
 : m_componentProviderMock(nullptr)
{
}

const ComponentProviderMock &CarouselBootloaderProviderMock::componentProvider() const
{
    return *m_componentProviderMock;
}

//------------------------------------------------------------------------------
IComponentProvider *CarouselBootloaderProviderMock::createComponentProvider()
{
    if (m_componentProviderMock == nullptr)
        m_componentProviderMock = new ComponentProviderMock();

    return m_componentProviderMock;
}

//------------------------------------------------------------------------------

