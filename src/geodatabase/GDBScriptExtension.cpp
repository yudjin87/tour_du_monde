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

#include <components/qmlscripting/IScriptingService.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtQml/QQmlEngine>
#include <QtQml/QJSValue>
#include <QtQml/QtQml>

GDBScriptExtension::GDBScriptExtension(QObject *parent)
    : QObject(parent)
{

}

void GDBScriptExtension::configureEngine(IServiceLocator *locator, QJSEngine *engine)
{
    IShapeFileWorkspaceFactory* factory = locator->locate<IShapeFileWorkspaceFactory>();
    QJSValue jsFactory = engine->newQObject(factory);
    QQmlEngine::setObjectOwnership(factory, QQmlEngine::CppOwnership);
    engine->globalObject().setProperty("shapeFileWorkspaceFactory", jsFactory);

    qmlRegisterInterface<IDataset>("IDataset");
    qmlRegisterInterface<IFeature>("IFeature");
    qmlRegisterInterface<IWorkspace>("IWorkspace");
    qmlRegisterInterface<IRecord>("IRecord");
    qmlRegisterInterface<IFeatureClass>("IFeatureClass");
    qmlRegisterInterface<IFeatureWorkspace>("IFeatureWorkspace");
    qmlRegisterInterface<IFeatureDataset>("IFeatureDataset");
}

