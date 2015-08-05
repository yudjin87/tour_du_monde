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

#include "cartoPersist/LegendClassPersist.h"
#include "cartoPersist/ISymbolPersist.h"
#include "cartoPersist/SymbolPersistCreator.h"
#include <carto/LegendClass.h>
#include <display/ISymbol.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

LegendClassPersist::LegendClassPersist()
{
}

void LegendClassPersist::save(QJsonObject &obj, const ILegendClass &legend)
{
    obj.insert("description", legend.description());
    obj.insert("label", legend.label());
    obj.insert("visibility", legend.isVisible());

    // symbol
    QJsonObject jsonSymbolData;
    SymbolPersistCreator creator;
    ISymbolPersistUPtr rendererPersist = creator.create(*legend.symbol());
    rendererPersist->save(jsonSymbolData);

    QJsonObject jsonSymbol;
    jsonSymbol.insert("type", toString(legend.symbol()->type()));
    jsonSymbol.insert("data", jsonSymbolData);

    obj.insert("symbol", jsonSymbol);
}

ILegendClassUPtr LegendClassPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "LegendClassPersist: empty object";
        return nullptr;
    }

    LegendClassUPtr legend(new LegendClass());
    const QString description = obj.value("description").toString();
    const QString label = obj.value("label").toString();
    const bool visibility = obj.value("visibility").toBool();
    legend->setDescription(description);
    legend->setLabel(label);
    legend->setVisible(visibility);

    // symbol
    const QJsonObject jsonSymbol = obj.value("symbol").toObject();
    const QString typeName = jsonSymbol.value("type").toString();
    const SymbolType type = symbolTypeFromString(typeName);
    if (!verifyEnum(type))
    {
        if (error) *error = "LegendClassPersist: Invalid symbol type";
        return nullptr;
    }

    SymbolPersistCreator creator;
    const QJsonObject jsonSymbolData = jsonSymbol.value("data").toObject();
    ISymbolPersistUPtr symbolPersist = creator.create(type);
    ISymbolUPtr symbol = symbolPersist->load(jsonSymbolData, error);
    if (symbol == nullptr)
    {
        return nullptr;
    }

    legend->setSymbol(symbol.release());
    return std::move(legend);
}
