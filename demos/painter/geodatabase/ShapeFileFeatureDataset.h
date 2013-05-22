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

#ifndef SHAPEFILEFEATUREDATASET_H
#define SHAPEFILEFEATUREDATASET_H

#include "IFeatureDataset.h"

class IServiceLocator;
class IWorkspace;
class QFile;

// shp + shx + dbf = dataset (for shapes)
class ShapeFileFeatureDataset : public IFeatureDataset
{
public:
    ShapeFileFeatureDataset(IWorkspace &workspace, const QString &name, IServiceLocator *locator);
    ~ShapeFileFeatureDataset();

    GeometryType geometryType();

    QRectF extent();

    QString name() const;
    IWorkspace &workspace() const;

    QList<IFeatureClass *> classes();
    IFeatureClass* classById(int id);
    IFeatureClass* classByName(const QString &className = "");

protected:
    virtual IFeatureClass* createFeatureClass(GeometryType geometryType, const QRectF &extent);

private:
    bool prepareToReading(const QString &name);
    void finishReading();

private:
    static const QString m_shapeFileExt;
    IWorkspace &m_workspace;
    QString m_name;
    IServiceLocator *m_locator;
    QFile *mp_file;
    bool m_isOpen;
};

#endif // SHAPEFILEFEATUREDATASET_H

