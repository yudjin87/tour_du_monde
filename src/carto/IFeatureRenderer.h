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
#include <carto/RendererType.h>

#include <QtCore/QObject>
#include <memory>

class IFeature;
class IFeatureRendererVisitor;
class ISymbol;
class ILegendGroup;
class QPainter;

class CARTO_API IFeatureRenderer : public QObject
{
    Q_OBJECT

public:
    IFeatureRenderer(QObject *parent = nullptr) : QObject(parent){}
    virtual ~IFeatureRenderer(){}

    virtual RendererType type() const = 0;

    /*!
     * @details
     *   Draws features from the specified cursor on the given device.
     *
     *   This method is typically called by the framework to renderer features
     *   to a device. This could be in response to a refresh on the map.
     *   This method typically iterates through all the features and renders each
     *   feature with an appropriate symbol.
     */
    virtual void draw(const QVector<IFeature *> &features, QPainter *painter) = 0;

    virtual ILegendGroup *legend() = 0;
    virtual const ILegendGroup *legend() const = 0;

    virtual void accept(IFeatureRendererVisitor& visitor) = 0;
    virtual IFeatureRenderer* clone() const = 0;
};

typedef std::unique_ptr<IFeatureRenderer> IFeatureRendererUPtr;

