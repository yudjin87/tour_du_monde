#include "FakeComponentLoader.h"

#include "MockComponent.h"

//------------------------------------------------------------------------------
FakeComponentLoader::FakeComponentLoader()
    : IComponentLoader()
    , instanceCalled(0)
    , loadCalled(0)
    , unloadCalled(0)
    , setFileNameCalled(0)
    , loadResult(true)
    , unloadResult(true)
    , passedFileName("")
    , mockComponent(new MockComponent())
{
}

//------------------------------------------------------------------------------
FakeComponentLoader::FakeComponentLoader(IComponent *component)
    : IComponentLoader()
    , instanceCalled(0)
    , loadCalled(0)
    , unloadCalled(0)
    , setFileNameCalled(0)
    , loadResult(true)
    , unloadResult(true)
    , passedFileName("")
    , mockComponent(component)
{
}

//------------------------------------------------------------------------------
FakeComponentLoader::~FakeComponentLoader()
{
    delete mockComponent;
    mockComponent = nullptr;
}

//------------------------------------------------------------------------------
QString FakeComponentLoader::errorString() const
{
    return "";
}

//------------------------------------------------------------------------------
QString FakeComponentLoader::fileName() const
{
    return passedFileName;
}

//------------------------------------------------------------------------------
IComponent *FakeComponentLoader::instance()
{
    ++instanceCalled;
    return mockComponent;
}

//------------------------------------------------------------------------------
bool FakeComponentLoader::isLoaded() const
{
    return loadResult;
}

//------------------------------------------------------------------------------
bool FakeComponentLoader::load()
{
    ++loadCalled;
    return loadResult;
}

//------------------------------------------------------------------------------
QLibrary::LoadHints FakeComponentLoader::loadHints() const
{
    return QLibrary::LoadArchiveMemberHint;
}

//------------------------------------------------------------------------------
void FakeComponentLoader::setFileName(const QString &fileName)
{
    Q_UNUSED(fileName)
    passedFileName = fileName;
    ++setFileNameCalled;
}

//------------------------------------------------------------------------------
void FakeComponentLoader::setLoadHints(QLibrary::LoadHints loadHints)
{
    Q_UNUSED(loadHints)
}

//------------------------------------------------------------------------------
bool FakeComponentLoader::deleteInstance()
{
    ++unloadCalled;
    emit unloaded();
    return unloadResult;
}

//------------------------------------------------------------------------------
