#include "MockComponentLoader.h"

//------------------------------------------------------------------------------
MockComponentLoader::MockComponentLoader(QObject *parent)
    : ComponentLoader(parent)
    , instanceCalled(0)
    , loadCalled(0)
    , unloadCalled(0)
{
}

//------------------------------------------------------------------------------
MockComponentLoader::MockComponentLoader(const QString &fileName, QObject *parent)
    : ComponentLoader(fileName, parent)
    , instanceCalled(0)
    , loadCalled(0)
    , unloadCalled(0)
{
}

//------------------------------------------------------------------------------
MockComponentLoader::~MockComponentLoader()
{    
}

//------------------------------------------------------------------------------
IComponent *MockComponentLoader::instance()
{
    ++instanceCalled;
    return ComponentLoader::instance();
}

//------------------------------------------------------------------------------
IComponent *MockComponentLoader::getInstance()
{
    return mp_instance;
}

//------------------------------------------------------------------------------
bool MockComponentLoader::load()
{
    ++loadCalled;
    return ComponentLoader::load();
}

//------------------------------------------------------------------------------
bool MockComponentLoader::deleteInstance()
{
    ++unloadCalled;
    emit unloaded();
    return ComponentLoader::deleteInstance();
}

//------------------------------------------------------------------------------
