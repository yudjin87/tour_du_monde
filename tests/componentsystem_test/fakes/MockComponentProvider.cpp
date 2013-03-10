#include "MockComponentProvider.h"

//------------------------------------------------------------------------------
MockComponentProvider::MockComponentProvider()
    : m_hasBeenInit(false)
{
}

//------------------------------------------------------------------------------
bool MockComponentProvider::hasBeenInit() const
{
    return m_hasBeenInit;
}

//------------------------------------------------------------------------------
bool MockComponentProvider::_initialize()
{
    m_hasBeenInit = true;

    return true;
}

//------------------------------------------------------------------------------
