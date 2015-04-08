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

#pragma once
#include <geodatabase/IFeatureClass.h>
#include <geodatabase/ITable.h>

class FeatureClass : public IFeatureClass
{
    Q_OBJECT
public:
    FeatureClass(ITable* table, Geometry::Type shapeType, const QRectF &extent, QString source);
    ~FeatureClass();

    QRectF extent() const override;

    Geometry::Type shapeType() const override;

    IFeature *createFeature() override;
    const IFeature *featureById(const int id) const override;
    const IFeature *featureByIndex(const int index) const override;

    const ITable* table() const override;
    IFeatureCollection search(const ISpatialFilter &filter) const override;

    const QString &source() const override;
    int featuresCount() const override;

private:
    Geometry::Type m_type;
    ITableUPtr m_table;
    IFeatureCollection m_features;
    QRectF m_extent;
    QString m_source;
};

