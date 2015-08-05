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

#include "cartoPersist/FeatureClassPersist.h"

#include <geodatabase/IFeatureWorkspace.h>
#include <geodatabase/IShapeFileWorkspaceFactory.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

FeatureClassPersist::FeatureClassPersist()
{
}

void FeatureClassPersist::save(QJsonObject &obj, const IFeatureClass &featureClass)
{
    obj.insert("workspacePath", featureClass.workspace()->pathName());
    obj.insert("name", featureClass.name());
}

IFeatureClassUPtr FeatureClassPersist::load(const QJsonObject &obj, IServiceLocator &serviceLocator, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "FeatureClassPersist: empty object";
        return nullptr;
    }

    const QVariant workspacePath = obj.value("workspacePath");
    if (!workspacePath.isValid())
    {
        if (error) *error = "Invalid workspacePath";
        return nullptr;
    }

    const QVariant name = obj.value("name");
    if (!name.isValid())
    {
        if (error) *error = "Invalid name";
        return nullptr;
    }

    IShapeFileWorkspaceFactory* wsFactory = serviceLocator.locate<IShapeFileWorkspaceFactory>();
    IFeatureWorkspace* ws = static_cast<IFeatureWorkspace*>(wsFactory->openFromFile(workspacePath.toString()));
    if (ws == nullptr)
    {
        if (error) *error = QString("Can't open workspace \"%1\"").arg(workspacePath.toString());
        return nullptr;
    }

    IFeatureClassUPtr featureClass(ws->openFeatureClass(name.toString()));
    if (featureClass == nullptr)
    {
        if (error) *error = QString("Can't open feature class \"%1\"").arg(name.toString());
        return nullptr;
    }

    return featureClass;
}
