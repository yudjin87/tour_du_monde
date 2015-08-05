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

#include "cartoPersist/SimpleLineSymbolPersist.h"
#include "cartoPersist/LegendGroupPersist.h"
#include <display/SimpleLineSymbol.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

SimpleLineSymbolPersist::SimpleLineSymbolPersist()
    : ISymbolPersist()
    , m_symbol(nullptr)
{

}

SimpleLineSymbolPersist::SimpleLineSymbolPersist(const SimpleLineSymbol &symbol)
    : ISymbolPersist()
    , m_symbol(&symbol)
{
}

void SimpleLineSymbolPersist::save(QJsonObject &obj)
{
    obj.insert("penStyle", m_symbol->style());
    obj.insert("width", m_symbol->width());
    obj.insert("color", m_symbol->color().name());
}

ISymbolUPtr SimpleLineSymbolPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "SimpleLineSymbolPersist: empty object";
        return nullptr;
    }

    const QJsonValue jsonPenStyle = obj.value("penStyle");
    const QJsonValue jsonWidth = obj.value("width");
    const QJsonValue jsonColor = obj.value("color");

    SimpleLineSymbolUPtr symbol(new SimpleLineSymbol());
    symbol->setStyle(static_cast<Qt::PenStyle>(jsonPenStyle.toInt()));
    symbol->setWidth(jsonWidth.toDouble());
    symbol->setColor(QColor(jsonColor.toString()));

    return std::move(symbol);
}

