#include "MockServiceLocator.h"

//------------------------------------------------------------------------------
MockServiceLocator::MockServiceLocator()
{
}

//------------------------------------------------------------------------------
const TypeObjectsMap<factoryMethod> &MockServiceLocator::creators() const
{
    return *mp_creators;
}

//------------------------------------------------------------------------------
const TypeObjectsMap<void *> &MockServiceLocator::items() const
{
    return *mp_objects;
}

//------------------------------------------------------------------------------
