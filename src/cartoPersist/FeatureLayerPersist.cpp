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

#include "cartoPersist/FeatureLayerPersist.h"
#include "cartoPersist/FeatureClassPersist.h"
#include "cartoPersist/FeatureRendererPersistCreator.h"
#include "cartoPersist/IFeatureRendererPersist.h"

#include <carto/FeatureLayer.h>
#include <carto/AbstractLayer.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

FeatureLayerPersist::FeatureLayerPersist()
    : FeatureLayerPersist(nullptr)
{
}

FeatureLayerPersist::FeatureLayerPersist(const FeatureLayer &layer)
    : ILayerPersist()
    , m_layer(&layer)
{
}

void FeatureLayerPersist::save(QJsonObject &obj)
{
    Q_ASSERT(m_layer != nullptr);

    // general info
    obj.insert("displayName", m_layer->name());
    obj.insert("isVisible", m_layer->isVisible());
    obj.insert("minimumScale", m_layer->minimumScale());
    obj.insert("maximumScale", m_layer->maximumScale());

    // feature class
    QJsonObject jsonFeatureClass;
    FeatureClassPersist featureClassPersist;
    featureClassPersist.save(jsonFeatureClass, *m_layer->featureClass());

    obj.insert("featureClass", jsonFeatureClass);

    // renderer
    QJsonObject jsonFeatureRendererData;
    FeatureRendererPersistCreator creator;
    IFeatureRendererPersistUPtr rendererPersist = creator.create(*m_layer->renderer());
    rendererPersist->save(jsonFeatureRendererData);

    QJsonObject jsonFeatureRenderer;
    jsonFeatureRenderer.insert("type", toString(m_layer->renderer()->type()));
    jsonFeatureRenderer.insert("data", jsonFeatureRendererData);

    obj.insert("featureRenderer", jsonFeatureRenderer);
}

AbstractLayerUPtr FeatureLayerPersist::load(const QJsonObject &obj, IServiceLocator &serviceLocator, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "FeatureLayerPersist: empty object";
        return nullptr;
    }

    FeatureLayerUPtr layer(new FeatureLayer());

    // feature class
    const QJsonObject jsonFeatureClass = obj.value("featureClass").toObject();
    FeatureClassPersist featureClassPersist;
    IFeatureClassUPtr featureClass = featureClassPersist.load(jsonFeatureClass, serviceLocator, error);
    if (featureClass == nullptr)
    {
        return nullptr;
    }

    layer->setFeatureClass(featureClass.release());

    // renderer
    const QJsonObject jsonFeatureRenderer = obj.value("featureRenderer").toObject();

    const QString typeName = jsonFeatureRenderer.value("type").toString();
    const RendererType type = rendererTypeFromString(typeName);
    if (!verifyEnum(type))
    {
        if (error) *error = QString("Invalid renderer type: \"%1\"").arg(typeName);
        return nullptr;
    }

    const QJsonObject jsonFeatureRendererData = jsonFeatureRenderer.value("data").toObject();
    FeatureRendererPersistCreator creator;
    IFeatureRendererPersistUPtr featureLayerRendererPersist = creator.create(type);
    IFeatureRendererUPtr renderer = featureLayerRendererPersist->load(jsonFeatureRendererData, error);
    if (renderer == nullptr)
    {
        return nullptr;
    }

    layer->setRenderer(renderer.release());
    return std::move(layer);
}
