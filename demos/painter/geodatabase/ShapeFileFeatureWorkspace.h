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

#ifndef SHAPEFILEFEATUREWORKSPACE_H
#define SHAPEFILEFEATUREWORKSPACE_H

#include "geodatabase_api.h"
#include "IFeatureWorkspace.h"

class IServiceLocator;

class GEODATABASE_API ShapeFileFeatureWorkspace : public IFeatureWorkspace
{
    Q_OBJECT
public:
    ShapeFileFeatureWorkspace(const QString &workspacePath, IServiceLocator *locator);
    ~ShapeFileFeatureWorkspace();

    OwnedList<IDataset *> *datasets(esriDatasetType byType);

    QString pathName() const;

    IFeatureClass *openFeatureClass(const QString &name);

private:
    QString m_workspacePath;
    IServiceLocator *m_locator;
};

#endif // SHAPEFILEFEATUREWORKSPACE_H
