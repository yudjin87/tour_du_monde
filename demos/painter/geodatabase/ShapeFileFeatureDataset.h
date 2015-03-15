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

#include "IFeatureDataset.h".
#include "geodatabase/IShapeFileReader.h"
#include "geometry/IGeometryFactory.h"

class IWorkspace;
class QFile;

// shp + shx + dbf = dataset (for shapes)
class ShapeFileFeatureDataset : public IFeatureDataset
{
    Q_OBJECT
public:
    ShapeFileFeatureDataset(IWorkspace &workspace, const QString &name);
    ~ShapeFileFeatureDataset();

    GeometryType geometryType() override;

    QRectF extent() override;

    QString name() const override;
    IWorkspace *workspace() const override;

    QList<IFeatureClass *> classes() override;
    IFeatureClass* classById(int id) override;
    IFeatureClass* classByName(const QString &className = "") override;

protected:
    virtual IFeatureClass* createFeatureClass(GeometryType geometryType, const QRectF &extent, const QString &source);

private:
    bool prepareToReading(const QString &name);
    void finishReading();
    QString absoluteFilePath(const QString &name);

private:
    static const QString m_shapeFileExt;
    IWorkspace &m_workspace;
    IShapeFileReaderUPtr m_fileReader;
    IGeometryFactoryUPtr m_factory;
    QString m_name;
    QFile *m_file;
    bool m_isOpen;
};

#endif // SHAPEFILEFEATUREDATASET_H

