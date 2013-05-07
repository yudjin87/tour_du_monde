#include "MockServiceLocator.h"

//------------------------------------------------------------------------------
MockServiceLocator::MockServiceLocator()
{
}

//------------------------------------------------------------------------------
const TypeObjectsMap<factoryMethod> &MockServiceLocator::creators() const
{
    return *m_creators;
}

//------------------------------------------------------------------------------
const TypeObjectsMap<void *> &MockServiceLocator::items() const
{
    return *m_objects;
}

//------------------------------------------------------------------------------
