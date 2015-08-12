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
#include <QtCore/QObject>
#include <memory>

class IFeatureRenderer;

class STYLES_API IFeatureLayerStyle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString layerName READ layerName WRITE setLayerName NOTIFY layerNameChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
public:
    virtual IFeatureLayerStyle* clone() const = 0;

    virtual QString layerName() const = 0;
    virtual void setLayerName(const QString &layerName) = 0;

    virtual QString name() const = 0;
    virtual void setName(const QString& name) = 0;

    virtual const IFeatureRenderer* renderer() const = 0;
    virtual void setRenderer(const IFeatureRenderer* renderer) = 0;

signals:
    void layerNameChanged(const QString &layerName);
    void nameChanged(const QString& name);
    void rendererChanged(const IFeatureRenderer* renderer);
};

typedef std::unique_ptr<IFeatureLayerStyle> IFeatureLayerStyleUPtr;
