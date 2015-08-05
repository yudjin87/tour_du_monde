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

#include "cartoPersist/PictureMarkerSymbolPersist.h"
#include "cartoPersist/LegendGroupPersist.h"
#include <display/PictureMarkerSymbol.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

PictureMarkerSymbolPersist::PictureMarkerSymbolPersist()
    : ISymbolPersist()
    , m_symbol(nullptr)
{

}

PictureMarkerSymbolPersist::PictureMarkerSymbolPersist(const PictureMarkerSymbol &symbol)
    : ISymbolPersist()
    , m_symbol(&symbol)
{
}

void PictureMarkerSymbolPersist::save(QJsonObject &obj)
{
    obj.insert("source", m_symbol->source());

    // MarkerSymbol
    obj.insert("angle", m_symbol->angle());
    obj.insert("size", m_symbol->size());
    obj.insert("color", m_symbol->color().name());
}

ISymbolUPtr PictureMarkerSymbolPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "PictureMarkerSymbolPersist: empty object";
        return nullptr;
    }

    // MarkerSymbol
    const QJsonValue jsonAngle = obj.value("angle");
    const QJsonValue jsonSize = obj.value("size");
    const QJsonValue jsonColor = obj.value("color");

    // PictureMarkerSymbol
    const QJsonValue jsonSource = obj.value("source");

    PictureMarkerSymbolUPtr symbol(new PictureMarkerSymbol());
    symbol->setAngle(jsonAngle.toDouble());
    symbol->setSize(jsonSize.toDouble());
    symbol->setColor(QColor(jsonColor.toString()));

    if (!symbol->loadFromFile(jsonSource.toString()))
    {
        if (error) *error = QString("PictureMarkerSymbolPersist: can't load picture \"%1\"").arg(jsonSource.toString());
        return nullptr;
    }

    return std::move(symbol);
}

