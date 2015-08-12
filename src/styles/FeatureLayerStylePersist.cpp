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

#include "styles/FeatureLayerStylePersist.h"
#include "styles/FeatureLayerStyle.h"
#include <cartoPersist/FeatureRendererPersistCreator.h>

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QByteArray>
#include <QtCore/QFile>

FeatureLayerStylePersist::FeatureLayerStylePersist()
{

}

bool FeatureLayerStylePersist::save(const IFeatureLayerStyle &style, const QString &fileName)
{
    QJsonObject jsonStyleRenderer;
    FeatureRendererPersistCreator creator;
    IFeatureRendererPersistUPtr rendererPersist = creator.create(*style.renderer());
    rendererPersist->save(jsonStyleRenderer);

    QJsonObject jsonLayerStyle;
    jsonLayerStyle.insert("name", style.name());
    jsonLayerStyle.insert("layerName", style.layerName());
    jsonLayerStyle.insert("renderer", jsonStyleRenderer);

    QJsonDocument jsonDoc(jsonLayerStyle);
    const QByteArray result = jsonDoc.toJson(QJsonDocument::Indented);

    QFile jsonFile(fileName);
    if (!jsonFile.open(QIODevice::WriteOnly))
    {
        return false;
    }

    return jsonFile.write(result) == result.size();
}

IFeatureLayerStyleUPtr FeatureLayerStylePersist::load(const QString &fileName)
{
    FeatureLayerStyleUPtr loadedStyle;
    return std::move(loadedStyle);
}

