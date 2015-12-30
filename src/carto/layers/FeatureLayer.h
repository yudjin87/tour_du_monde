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
#include <carto/layers/AbstractLayer.h>
#include <carto/renderers/IFeatureRenderer.h>
#include <geometry/GeometryType.h>

#include <QtCore/QList>
#include <memory>

class IFeatureRenderer;
class IFeatureClass;

class CARTO_API FeatureLayer : public AbstractLayer
{
    Q_OBJECT
    Q_PROPERTY(Geometry::Type shapeType READ shapeType)
    Q_PROPERTY(IFeatureClass *featureClass READ featureClass WRITE setFeatureClass)
    Q_PROPERTY(IFeatureRenderer *renderer READ renderer)
public:
    FeatureLayer(QObject *parent = nullptr);
    ~FeatureLayer();

    LayerType type() const;
    Geometry::Type shapeType() const;

    IFeatureRenderer *renderer();
    const IFeatureRenderer *renderer() const;
    void setRenderer(IFeatureRenderer *newRenderer);

    void draw(IDisplay *display) override;

    QRectF extent() const override;

    IFeatureClass *featureClass();
    const IFeatureClass *featureClass() const;

    void setFeatureClass(IFeatureClass *featureClass);

    void accept(ILayerVisitor& visitor) override;

signals:
    void rendererChanged(const IFeatureRenderer *newRenderer);

protected:
    void show() override;
    void hide() override;

private:
    IFeatureClass *m_featureClass;
    IFeatureRendererUPtr m_featureRenderer;
};

typedef std::unique_ptr<FeatureLayer> FeatureLayerUPtr;

