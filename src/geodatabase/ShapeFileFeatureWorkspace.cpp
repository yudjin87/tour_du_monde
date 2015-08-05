/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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

#include "geodatabase/ShapeFileFeatureWorkspace.h"
#include "geodatabase/FeatureClassLoader.h"
#include "geodatabase/FeatureClass.h"
#include "geodatabase/Table.h"
#include "geodatabase/winutils.h"
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

#include <chrono>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ShapeFileWorkspace");
static const char* DBF_FILE_EXT = "dbf";
}

ShapeFileFeatureWorkspace::ShapeFileFeatureWorkspace(const QString &workspacePath)
    : m_workspacePath()
    , m_dbfDb(nullptr)
{
    QDir dir(workspacePath);
    m_workspacePath = dir.absolutePath();
}

ShapeFileFeatureWorkspace::~ShapeFileFeatureWorkspace()
{
    delete m_dbfDb;
    m_dbfDb = nullptr;
}

OwnedList<IDataset *> *ShapeFileFeatureWorkspace::datasets(IWorkspace::esriDatasetType byType)
{
    Q_UNUSED(byType)
    return 0;
}

QString ShapeFileFeatureWorkspace::pathName() const
{
    return m_workspacePath;
}

IFeatureClass *ShapeFileFeatureWorkspace::openFeatureClass(const QString &name)
{
    ITable* table = createTable(name);

    typedef std::chrono::system_clock Clock;
    typedef std::chrono::milliseconds milliseconds;

    const Clock::time_point started = Clock::now();

    FeatureClassLoader loader(m_workspacePath);
    if (loader.open(name) != IFeatureClassLoader::LoadResult::Success)
    {
        return nullptr;
    }

    IFeatureClass* fc = new FeatureClass(*this, table, loader.geometryType(), loader.boundingBox(), loader.source().completeBaseName());
    while (loader.hasNext())
    {
        IFeature* feature = fc->createFeature();
        loader.loadFeature(feature);
    }

    Clock::time_point finished = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(finished - started);

    Log.d(QString("Reading %1 file: %2 ms").arg(name).arg(ms.count()));

    return fc;
}

bool ShapeFileFeatureWorkspace::checkWorkspace() const
{
    const QDir dir(m_workspacePath);
    if (!dir.exists())
    {
        Log.w(QString("Invalid workspace: path doesn't exist").arg(m_workspacePath));
        return false;
    }

    return true;
}

ITable *ShapeFileFeatureWorkspace::createTable(const QString &name)
{
    if (!checkWorkspace())
    {
        return nullptr;
    }

    const QDir dir(m_workspacePath);
    const QString dbfFileName = dir.absoluteFilePath(name);
    QFileInfo file = QFileInfo(dbfFileName);
    if (file.suffix().isEmpty())
    {
        file = dbfFileName + "." + DBF_FILE_EXT;
    }

    if (!file.exists())
    {
        return nullptr;
    }

    if (!file.isReadable())
    {
        return nullptr;
    }

    // TODO: refactor me
    if (m_dbfDb == nullptr)
    {
        QString error;
        QString shortPathName = utils::getShortPathName(pathName(), &error); // Windows workaround for long names for dBase
        if (shortPathName.isEmpty())
        {
            Log.e(error);
            return nullptr;
        }

        const QString dbfName = QString("DRIVER={Microsoft dBase Driver (*.dbf)};FIL={dBase IV;};DefaultDir=%1").arg(shortPathName);
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        db.setDatabaseName(dbfName);
        if (!db.open())
        {
            Log.e(db.lastError().text());
            return nullptr;
        }

        m_dbfDb = new QSqlDatabase(db);
    }

    return new Table(*this, file.completeBaseName(), *m_dbfDb);
}
