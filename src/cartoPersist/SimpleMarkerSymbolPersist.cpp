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

#include "cartoPersist/SimpleMarkerSymbolPersist.h"
#include "cartoPersist/LegendGroupPersist.h"
#include <display/SimpleMarkerSymbol.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

SimpleMarkerSymbolPersist::SimpleMarkerSymbolPersist()
    : ISymbolPersist()
    , m_symbol(nullptr)
{

}

SimpleMarkerSymbolPersist::SimpleMarkerSymbolPersist(const SimpleMarkerSymbol &symbol)
    : ISymbolPersist()
    , m_symbol(&symbol)
{
}

void SimpleMarkerSymbolPersist::save(QJsonObject &obj)
{
    obj.insert("style", static_cast<int>(m_symbol->style()));
    obj.insert("outlineSize", m_symbol->outlineSize());
    obj.insert("isOutline", m_symbol->isOutline());
    obj.insert("outlineColor", m_symbol->outlineColor().name());

    // MarkerSymbol
    obj.insert("angle", m_symbol->angle());
    obj.insert("size", m_symbol->size());
    obj.insert("color", m_symbol->color().name());
}

ISymbolUPtr SimpleMarkerSymbolPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "SimpleMarkerSymbolPersist: empty object";
        return nullptr;
    }

    // MarkerSymbol
    const QJsonValue jsonAngle = obj.value("angle");
    const QJsonValue jsonSize = obj.value("size");
    const QJsonValue jsonColor = obj.value("color");

    // SimpleMarkerSymbol
    const QJsonValue jsonStyle = obj.value("style");
    const QJsonValue jsonOutlineSize = obj.value("outlineSize");
    const QJsonValue jsonIsOutline = obj.value("isOutline");
    const QJsonValue jsonOutlineColor = obj.value("outlineColor");

    SimpleMarkerSymbolUPtr symbol(new SimpleMarkerSymbol());
    symbol->setAngle(jsonAngle.toDouble());
    symbol->setSize(jsonSize.toDouble());
    symbol->setColor(QColor(jsonColor.toString()));

    symbol->setStyle(static_cast<SimpleMarkerSymbol::Style>(jsonStyle.toInt()));
    symbol->setOutlineSize(jsonOutlineSize.toDouble());
    symbol->setOutline(jsonIsOutline.toBool());
    symbol->setOutlineColor(QColor(jsonOutlineColor.toString()));

    return std::move(symbol);
}

