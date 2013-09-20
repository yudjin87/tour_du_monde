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

#ifndef FEATURECLASS_H
#define FEATURECLASS_H

#include "IFeatureClass.h"

class FeatureClass : public IFeatureClass
{
    Q_OBJECT
public:
    FeatureClass(GeometryType shapeType, const QRectF &extent, QString source);
    ~FeatureClass();

    QRectF extent() const override;

    GeometryType shapeType() const override;

    IFeature *createFeature() override;
    const FeatureList &features() const override;

    FeatureList search(const ISpatialFilter &filter) const override;

    const QString &source() const override;

private:
    GeometryType m_type;
    FeatureList m_features;
    QRectF m_extent;
    QString m_source;
};

#endif // FEATURECLASS_H
