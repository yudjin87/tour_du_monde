/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
 *
 * This program or library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA
 *
 * END_COMMON_COPYRIGHT_HEADER */

#include "componentsystem/ComponentLoader.h"
#include "componentsystem/IComponent.h"
#include "componentsystem/ComponentExport.h"

#include "logging/LoggerFacade.h"

#include <QtCore/QFileInfo>
#include <QtCore/QLibrary>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ComponentLoader");
}

//------------------------------------------------------------------------------
const QString ComponentLoader::m_createFuncName = CREATE_FUNCTION_NAME;
const QString ComponentLoader::m_releaseFuncName = RELEASE_FUNCTION_NAME;

//------------------------------------------------------------------------------
ComponentLoader::ComponentLoader(QObject *parent)
    : QObject(parent)
    , m_instance(nullptr)
    , m_fileName("")
    , m_errorString("")
    , m_loaded(false)
    , m_loadHits(QLibrary::ResolveAllSymbolsHint | QLibrary::ExportExternalSymbolsHint)
    , m_createFunc(nullptr)
    , m_releaseFunc(nullptr)
    , m_library(nullptr)
{
}

//------------------------------------------------------------------------------
ComponentLoader::ComponentLoader(const QString &fileName, QObject *parent)
    : QObject(parent)
    , m_instance(nullptr)
    , m_fileName("")
    , m_errorString("")
    , m_loaded(false)
    , m_loadHits(QLibrary::ResolveAllSymbolsHint | QLibrary::ExportExternalSymbolsHint)
    , m_createFunc(nullptr)
    , m_releaseFunc(nullptr)
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

    return m_instance;
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

    if (m_fileName.isEmpty()) {
        Log.w("Cannot load component - file name is empty.");
        return false;
    }

    m_errorString = "";

    m_library = new QLibrary(m_fileName);
    m_library->setLoadHints(loadHints());
    if (!m_library->load()) {
        m_errorString = m_library->errorString();
        Log.e(QString("Cannot load component. Error: %1").arg(m_errorString));
        return false;
    }

    QFunctionPointer createFunc = m_library->resolve(m_createFuncName.toLatin1().data());
    m_createFunc = reinterpret_cast<createComponentFunc>(createFunc);
    if (m_createFunc == nullptr) {
        m_errorString = QString("Cannot found create function \"%1\" at the \"%2\". See internal error: %3")
                .arg(m_createFuncName, m_library->fileName(), m_library->errorString());
        Log.e(m_errorString);
        return false;
    }

    QFunctionPointer releaseFunc = m_library->resolve(m_releaseFuncName.toLatin1().data());
    m_releaseFunc = reinterpret_cast<releaseComponentFunc>(releaseFunc);
    if (m_releaseFunc == nullptr) {
        m_errorString = QString("Cannot found release function \"%1\" at the \"%2\". See internal error: %3")
                .arg(m_releaseFuncName, m_library->fileName(), m_library->errorString());
        Log.e(m_errorString);
        return false;
    }

    QObject *obj = reinterpret_cast<QObject *>(m_createFunc());
    m_instance = dynamic_cast<IComponent *>(obj);

    m_loaded = true;

    Log.d(QString("Component \"%1\" was successfully loaded.").arg(m_fileName));

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
    if (!file.exists()) {
        Log.w(QString("Cannot use \"%1\" file name. It does not exist.").arg(fileName));
        return;
    }

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
    if (!m_loaded)
        return true;

    if (!deleteInstance())
        return false;

    bool result = m_library->unload();
    delete m_library;
    m_library = nullptr;

    return result;
}

//------------------------------------------------------------------------------
bool ComponentLoader::deleteInstance()
{
    if (!m_loaded) {
        Log.w("Cannot delete instance, because it was not load.");
        return false;
    }

    Log.d("Delete loaded instance.");
    m_releaseFunc(m_instance);
    m_releaseFunc = nullptr;
    m_createFunc = nullptr;
    m_instance = nullptr;
    m_loaded = false;

    return true;
}

//------------------------------------------------------------------------------
