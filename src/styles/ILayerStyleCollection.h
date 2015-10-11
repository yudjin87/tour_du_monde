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

#pragma once

#include <styles/styles_api.h>
#include <styles/IFeatureLayerStyle.h>
#include <QtCore/QObject>
#include <memory>
#include <vector>

class STYLES_API ILayerStyleCollection : public QObject
{
    Q_OBJECT
public:
    typedef std::vector<IFeatureLayerStyleUPtr> ILayerStyleVector;

public:
    virtual void add(IFeatureLayerStyleUPtr layerStyle) = 0;

    virtual ILayerStyleVector::const_iterator begin() const = 0;
    virtual ILayerStyleVector::const_iterator end() const = 0;

    virtual ILayerStyleCollection* clone() const = 0;

public slots:
    virtual void add(IFeatureLayerStyle* layerStyle) = 0;
    virtual IFeatureLayerStyle* styleByName(const QString& name) const = 0;
    virtual IFeatureLayerStyle* styleByLayerName(const QString& layerName) const = 0;

signals:
    void collectionChanged();
};

typedef std::unique_ptr<ILayerStyleCollection> ILayerStyleCollectionUPtr;

