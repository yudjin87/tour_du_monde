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

#include <carto/carto_api.h>
#include <carto/IRendererCategory.h>
#include <carto/ILegendGroup.h>

#include <QtCore/QVariant>
#include <QtCore/QObject>

#include <memory>
#include <vector>

class CARTO_API IRendererCategoryCollection : public QObject
{
    Q_OBJECT
public:
    typedef std::vector<const IRendererCategoryUPtr> IRendererCategoryVector;

public:
    virtual void addCategory(IRendererCategory* category) = 0;
    virtual IRendererCategory* findByValue(const QVariant& value) = 0;
    virtual const IRendererCategory* findByValue(const QVariant& value) const = 0;

    virtual IRendererCategoryCollection* clone(ILegendGroup& clonedGroup) const = 0;

    virtual IRendererCategoryVector::const_iterator begin() const = 0;
    virtual IRendererCategoryVector::const_iterator end() const = 0;

    virtual void reset(ILegendGroup& newLegend) = 0;

signals:
    void categoryAdded(IRendererCategory* category);
    void categoryRemoved();
};

typedef std::unique_ptr<IRendererCategoryCollection> IRendererCategoryCollectionUPtr;
