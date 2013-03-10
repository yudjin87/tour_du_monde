#include "ComponentLoader.h"

#include "IComponent.h"
#include "ComponentExport.h"

#include <QtCore/QFileInfo>
#include <QtCore/QLibrary>

//------------------------------------------------------------------------------
const QString ComponentLoader::m_createFuncName = CREATE_FUNCTION_NAME;
const QString ComponentLoader::m_releaseFuncName = RELEASE_FUNCTION_NAME;

//------------------------------------------------------------------------------
ComponentLoader::ComponentLoader(QObject *parent)
    : QObject(parent)
    , mp_instance(nullptr)
    , m_fileName("")
    , m_errorString("")
    , m_loaded(false)
    , m_loadHits(QLibrary::ResolveAllSymbolsHint | QLibrary::ExportExternalSymbolsHint)
    , mp_createFunc(nullptr)
    , mp_releaseFunc(nullptr)
    , mp_library(nullptr)
{
}

//------------------------------------------------------------------------------
ComponentLoader::ComponentLoader(const QString &fileName, QObject *parent)
    : QObject(parent)
    , mp_instance(nullptr)
    , m_fileName("")
    , m_errorString("")
    , m_loaded(false)
    , m_loadHits(QLibrary::ResolveAllSymbolsHint | QLibrary::ExportExternalSymbolsHint)
    , mp_createFunc(nullptr)
    , mp_releaseFunc(nullptr)
{
    setFileName(fileName);
}

//------------------------------------------------------------------------------
ComponentLoader::~ComponentLoader()
{
    unload();
}

//------------------------------------------------------------------------------
QString ComponentLoader::errorString() const
{
    return m_errorString;
}

//------------------------------------------------------------------------------
QString ComponentLoader::fileName() const
{
    return m_fileName;
}

//------------------------------------------------------------------------------
IComponent *ComponentLoader::instance()
{
    if (!m_loaded)
        load();

    return mp_instance;
}

//------------------------------------------------------------------------------
bool ComponentLoader::isLoaded() const
{
    return m_loaded;
}

//------------------------------------------------------------------------------
bool ComponentLoader::load()
{
    if (m_loaded)
        return true;

    if (m_fileName.isEmpty())
        return false;

    m_errorString = "";

    mp_library = new QLibrary(m_fileName);
    mp_library->setLoadHints(loadHints());
    if (!mp_library->load()) {
        m_errorString = mp_library->errorString();
        return false;
    }

    void *createFunc = mp_library->resolve(m_createFuncName.toLatin1().data());
    mp_createFunc = reinterpret_cast<createComponentFunc>(createFunc);
    if (mp_createFunc == nullptr) {
        m_errorString = QString("Cannot found create function \"%1\" at the \"%2\".\nSee internal error:\n%3")
                .arg(m_createFuncName, mp_library->fileName(), mp_library->errorString());
        return false;
    }

    void *releaseFunc = mp_library->resolve(m_releaseFuncName.toLatin1().data());
    mp_releaseFunc = reinterpret_cast<releaseComponentFunc>(releaseFunc);
    if (mp_releaseFunc == nullptr) {
        m_errorString = QString("Cannot found release function \"%1\" at the \"%2\".\nSee internal error:\n%3")
                .arg(m_releaseFuncName, mp_library->fileName(), mp_library->errorString());
        return false;
    }

    QObject *obj = reinterpret_cast<QObject *>(mp_createFunc());
    mp_instance = dynamic_cast<IComponent *>(obj);

    m_loaded = true;
    return true;
}

//------------------------------------------------------------------------------
QLibrary::LoadHints ComponentLoader::loadHints() const
{
    return m_loadHits;
}

//------------------------------------------------------------------------------
void ComponentLoader::setFileName(const QString &fileName)
{
    QFileInfo file(fileName);
    if (!file.exists())
        return;

    if (m_loaded)
        return;

    m_fileName = fileName;
}

//------------------------------------------------------------------------------
void ComponentLoader::setLoadHints(QLibrary::LoadHints loadHints)
{
    m_loadHits = loadHints;
}

//------------------------------------------------------------------------------
bool ComponentLoader::unload()
{
    if (!deleteInstance())
        return false;

    bool result = mp_library->unload();
    delete mp_library;
    mp_library = nullptr;

    return result;
}

//------------------------------------------------------------------------------
bool ComponentLoader::deleteInstance()
{
    if (!m_loaded)
        return false;

    mp_releaseFunc(mp_instance);
    mp_releaseFunc = nullptr;
    mp_createFunc = nullptr;
    mp_instance = nullptr;
    m_loaded = false;

    return true;
}

//------------------------------------------------------------------------------
