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

#include "GDBScriptExtension.h"
#include "IDataset.h"
#include "IFeature.h"
#include "IRecord.h"
#include "IFeatureClass.h"
#include "IFeatureWorkspace.h"
#include "IFeatureDataset.h"
#include "IGeoDataset.h"
#include "IShapeFileWorkspaceFactory.h"
#include "ISpatialFilter.h"
#include "IWorkspace.h"
#include "IWorkspaceFactory.h"

#include <components/jsscripting/IScriptingService.h>
#include <components/jsscripting/IScriptConsole.h>

#include <QtCore/QMetaType>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>

Q_DECLARE_METATYPE(Geometry::Type)

namespace
{
int registerFeatureList(QScriptEngine *engine)
{
    return qScriptRegisterMetaType<QVector<IFeature *>>(engine,
        qScriptValueFromSequence<QVector<IFeature *>>,
        qScriptValueToSequence<QVector<IFeature *>>);
}

int registerFeatureClassList(QScriptEngine *engine)
{
    return qScriptRegisterMetaType<QVector<IFeatureClass *>>(engine,
        qScriptValueFromSequence<QVector<IFeatureClass *>>,
        qScriptValueToSequence<QVector<IFeatureClass *>>);
}

} // namespace

GDBScriptExtension::GDBScriptExtension(QObject *parent)
    : QObject(parent)
{

}

void GDBScriptExtension::configureEngine(IServiceLocator *locator, QScriptEngine *engine)
{
    Q_UNUSED(locator)

    int featureListId = registerFeatureList(engine); Q_UNUSED(featureListId);
    int featureClassListId = registerFeatureClassList(engine); Q_UNUSED(featureClassListId);

    REGISTER_METATYPE(IDataset);
    REGISTER_METATYPE(IFeature);
    REGISTER_METATYPE(IRecord);
    REGISTER_METATYPE(IFeatureWorkspace);
    REGISTER_METATYPE(IFeatureClass);
    REGISTER_METATYPE(IFeatureDataset);
    REGISTER_METATYPE(IGeoDataset);
    REGISTER_METATYPE(IShapeFileWorkspaceFactory);
    REGISTER_METATYPE(ISpatialFilter);
    REGISTER_METATYPE(IWorkspace);
    REGISTER_METATYPE(IWorkspaceFactory);
}

