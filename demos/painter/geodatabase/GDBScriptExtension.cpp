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

#include "GDBScriptExtension.h"
#include "IDataset.h"
#include "IFeature.h"
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

//------------------------------------------------------------------------------
Q_DECLARE_METATYPE(GeometryType)

//------------------------------------------------------------------------------

// TODO: provide a macros with Q_UNUSED
static const int IDatasetId = qRegisterMetaType<IFeature *>("IDataset *");
static const int IFeatureId = qRegisterMetaType<IFeature *>("IFeature *");
static const int IFeatureClassId = qRegisterMetaType<IFeatureClass *>("IFeatureClass *");
static const int IFeatureWorkspaceId = qRegisterMetaType<IFeatureWorkspace *>("IFeatureWorkspace *");
static const int IFeatureDatasetId = qRegisterMetaType<IFeatureDataset *>("IFeatureDataset *");
static const int IGeoDatasetId = qRegisterMetaType<IGeoDataset *>("IGeoDataset *");
static const int IShapeFileWorkspaceFactoryId = qRegisterMetaType<IShapeFileWorkspaceFactory *>("IShapeFileWorkspaceFactory *");
static const int ISpatialFilterId = qRegisterMetaType<ISpatialFilter *>("ISpatialFilter *");
static const int IWorkspaceId = qRegisterMetaType<IWorkspace *>("IWorkspace *");
static const int IWorkspaceFactoryId = qRegisterMetaType<IWorkspaceFactory *>("IWorkspaceFactory *");

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
GDBScriptExtension::GDBScriptExtension(QObject *parent)
    : QObject(parent)
{

}

//------------------------------------------------------------------------------
void GDBScriptExtension::configureEngine(QScriptEngine *engine)
{
    int featureListId = registerFeatureList(engine); Q_UNUSED(featureListId);
    int featureClassListId = registerFeatureClassList(engine); Q_UNUSED(featureClassListId);
}

//------------------------------------------------------------------------------
