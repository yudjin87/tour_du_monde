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

#include "styles/StyleGalery.h"
#include "styles/LayerStyleCollection.h"
#include "styles/FeatureLayerStyle.h"
#include "styles/FeatureLayerStylePersist.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("StyleGalery");
}

StyleGalery::StyleGalery()
    : IStyleGalery()
    , m_styles()
{
}

QString StyleGalery::defaultStylesLocationPath() const
{
    QDir stylesDir(QCoreApplication::applicationDirPath());
    stylesDir.cd("styles");
    return stylesDir.absolutePath();
}

ILayerStyleCollectionUPtr StyleGalery::load() const
{
    const QDir stylesDir(defaultStylesLocationPath());
    if (!stylesDir.exists())
    {
        Log.w(QString("Styles directory \"%1\" doesn't exist").arg(stylesDir.absolutePath()));
        return nullptr;
    }

    FeatureLayerStylePersist persist;
    LayerStyleCollectionUPtr collection(new LayerStyleCollection());
    const QStringList files = stylesDir.entryList(QDir::Files, QDir::Name);
    for (const QString& styleFile : files)
    {
        IFeatureLayerStyleUPtr style = persist.load(styleFile);
        if (style == nullptr)
        {
            Log.w(QString("Can't load style \"%1\"").arg(styleFile));
        }
        else
        {
            collection->add(std::move(style));
        }
    }

    return std::move(collection);
}

bool StyleGalery::save(const ILayerStyleCollection &collection)
{
    const QDir stylesDir(defaultStylesLocationPath());
    if (!stylesDir.exists())
    {
        Log.w(QString("Styles directory \"%1\" doesn't exist").arg(stylesDir.absolutePath()));
        return false;
    }

    FeatureLayerStylePersist persist;
    for (const IFeatureLayerStyleUPtr& layerStyle : collection)
    {
        const QString& styleFile = stylesDir.absoluteFilePath(layerStyle->name() + ".json");
        if (!persist.save(*layerStyle, styleFile))
        {
            Log.w(QString("Can't save \"%1\" layer style").arg(layerStyle->name()));
        }
    }

    return true;
}

