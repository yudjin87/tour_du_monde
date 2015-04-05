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

#include "geodatabase/ShapeFileFeatureWorkspace.h"
#include "geodatabase/ShapeFileFeatureDataset.h"
#include "geodatabase/FeatureClassLoader.h"
#include "geodatabase/FeatureClass.h"
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QDir>
#include <QtCore/QFileInfo>

#include <chrono>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ShapeFileWorkspace");
}

ShapeFileFeatureWorkspace::ShapeFileFeatureWorkspace(const QString &workspacePath)
    : m_workspacePath()
{
    QDir dir(workspacePath);
    m_workspacePath = dir.absolutePath();
}

ShapeFileFeatureWorkspace::~ShapeFileFeatureWorkspace()
{
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
    typedef std::chrono::system_clock Clock;
    typedef std::chrono::milliseconds milliseconds;

    const Clock::time_point started = Clock::now();

    IFeatureClass* fc = nullptr;

#if 0
    ShapeFileFeatureDataset dataset(*this, name);
    fc = dataset.classByName(name);
#else
    FeatureClassLoader loader(m_workspacePath);
    if (loader.open(name) != IFeatureClassLoader::LoadResult::Success)
    {
        return nullptr;
    }

    fc = new FeatureClass(loader.geometryType(), loader.boundingBox(), loader.source().absoluteFilePath());
    while (loader.hasNext())
    {
        IFeature* feature = fc->createFeature();
        loader.loadFeature(feature);
    }
#endif

    Clock::time_point finished = Clock::now();
    milliseconds ms = std::chrono::duration_cast<milliseconds>(finished - started);

    Log.d(QString("Reading %1 file: %2 ms").arg(name).arg(ms.count()));

    return fc;
}


