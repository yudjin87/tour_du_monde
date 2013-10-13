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

#include "PersistenceService.h"
#include "CarouselPersistenceDelegate.h"

#include <carousel/componentsystem/IComponentManager.h>
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("PersistenceService");
}

//------------------------------------------------------------------------------
PersistenceService::PersistenceService(IServiceLocator *locator, IComponentManager *manager, QObject *parent)
    : IPersistenceService()
    , m_delegate(new CarouselPersistenceDelegate(locator))
    , m_manager(manager)
    , m_filePath()
{
    setParent(parent);
}

//------------------------------------------------------------------------------
PersistenceService::PersistenceService(IPersistenceDelegate *delegate, IComponentManager *manager, QObject *parent)
    : IPersistenceService()
    , m_delegate(delegate)
    , m_manager(manager)
    , m_filePath()
{
    setParent(parent);
}

//------------------------------------------------------------------------------
PersistenceService::~PersistenceService()
{
    delete m_delegate;
    m_delegate = nullptr;

    m_manager = nullptr;
}

//------------------------------------------------------------------------------
IPersistenceDelegate *PersistenceService::delegate()
{
    return m_delegate;
}

//------------------------------------------------------------------------------
const IPersistenceDelegate *PersistenceService::delegate() const
{
    return m_delegate;
}

//------------------------------------------------------------------------------
void PersistenceService::setDelegate(IPersistenceDelegate *delegate)
{
    delete m_delegate;
    m_delegate = delegate;
}

//------------------------------------------------------------------------------
QString PersistenceService::absoluteFilePath() const
{
    return m_filePath;
}

//------------------------------------------------------------------------------
QString PersistenceService::fileName() const
{
    QFileInfo file(m_filePath);
    return file.fileName();
}

//------------------------------------------------------------------------------
bool PersistenceService::save()
{
    return saveAs(m_filePath);
}

//------------------------------------------------------------------------------
bool PersistenceService::saveAs(const QString &filePath)
{
    if (filePath.isEmpty()) {
        Log.w("Saving: empty file name");
        return false;
    }

    QString fPath = absolutePath(filePath);
    if (!saveToFile(fPath))
        return false;

    m_filePath = fPath;
    emit fileNameChanged();

    return true;
}

//------------------------------------------------------------------------------
bool PersistenceService::load(const QString &filePath)
{
    m_filePath = absolutePath(filePath);
    emit fileNameChanged();
    return load();
}

//------------------------------------------------------------------------------
bool PersistenceService::load()
{
    if (m_delegate == nullptr) {
        Log.e("Null delegate - cannot save");
        return false;
    }

    if (m_filePath.isEmpty()) {
        Log.w("No file name specified");
        return false;
    }

    QFile documentFile(m_filePath);
    if (!documentFile.open(QIODevice::ReadOnly)) {
        QString error = QString("Selected file \"%1\" could not be opened!").arg(m_filePath);
        Log.w(error);
        return false;
    }

    Log.i(QString("Loading from the \"%1\"").arg(m_filePath));

    QByteArray loadedDoc = documentFile.readAll();
    if (!m_delegate->load(m_manager->startedComponents(), loadedDoc)) {
        Log.w("Failed to load document");
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------
bool PersistenceService::saveToFile(const QString &filePath)
{
    if (m_delegate == nullptr) {
        Log.e("Null delegate - cannot save");
        return false;
    }

    QFile documentFile(filePath);
    if (!documentFile.open(QIODevice::WriteOnly)) {
        QString error = QString("Selected file \"%1\" could not be opened!").arg(m_filePath);
        Log.w(error);
        return false;
    }

    Log.i(QString("Saving to the \"%1\"").arg(filePath));

    QTextStream out(&documentFile);
    QByteArray savedDoc;
    if (!m_delegate->save(m_manager->startedComponents(), savedDoc)) {
        Log.w("Failed to save document");
        return false;
    }

    out << savedDoc;
    return true;
}

//------------------------------------------------------------------------------
QString PersistenceService::absolutePath(const QString &filePath)
{
    QDir dir(QCoreApplication::applicationDirPath());
    return QDir::cleanPath(dir.absoluteFilePath(filePath));
}

//------------------------------------------------------------------------------
