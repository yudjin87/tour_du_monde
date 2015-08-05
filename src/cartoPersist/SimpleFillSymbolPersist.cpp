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

#include "cartoPersist/SimpleFillSymbolPersist.h"
#include "cartoPersist/SymbolPersistCreator.h"
#include "cartoPersist/LegendGroupPersist.h"
#include <display/SimpleFillSymbol.h>
#include <display/LineSymbol.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

SimpleFillSymbolPersist::SimpleFillSymbolPersist()
    : ISymbolPersist()
    , m_symbol(nullptr)
{

}

SimpleFillSymbolPersist::SimpleFillSymbolPersist(const SimpleFillSymbol &symbol)
    : ISymbolPersist()
    , m_symbol(&symbol)
{
}

void SimpleFillSymbolPersist::save(QJsonObject &obj)
{
    obj.insert("brushStyle", m_symbol->style());
    obj.insert("color", m_symbol->color().name());

    // FillSymbol
    QJsonObject jsonOutlineData;
    SymbolPersistCreator creator;
    ISymbolPersistUPtr rendererPersist = creator.create(*m_symbol->outline());
    rendererPersist->save(jsonOutlineData);

    QJsonObject jsonOutline;
    jsonOutline.insert("type", toString(m_symbol->outline()->type()));
    jsonOutline.insert("data", jsonOutlineData);

    obj.insert("outline", jsonOutline);
}

ISymbolUPtr SimpleFillSymbolPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "SimpleFillSymbolPersist: empty object";
        return nullptr;
    }

    const QJsonValue jsonBrushStyle = obj.value("brushStyle");
    const QJsonValue jsonColor = obj.value("color");

    // FillSymbol
    const QJsonObject jsonOutline = obj.value("outline").toObject();

    const QString typeName = jsonOutline.value("type").toString();
    const SymbolType type = symbolTypeFromString(typeName);
    if (!verifyEnum(type))
    {
        if (error) *error = "SimpleFillSymbolPersist: Invalid outline symbol type";
        return nullptr;
    }

    SymbolPersistCreator creator;
    const QJsonObject jsonOutlineData = jsonOutline.value("data").toObject();
    ISymbolPersistUPtr symbolPersist = creator.create(type);
    ISymbolUPtr outlineSymbol = symbolPersist->load(jsonOutlineData, error);
    if (outlineSymbol == nullptr)
    {
        return nullptr;
    }

    SimpleFillSymbolUPtr symbol(new SimpleFillSymbol());
    symbol->setStyle(static_cast<Qt::BrushStyle>(jsonBrushStyle.toInt()));
    symbol->setColor(QColor(jsonColor.toString()));
    symbol->setOutline(static_cast<LineSymbol*>(outlineSymbol.release()));

    return std::move(symbol);
}

