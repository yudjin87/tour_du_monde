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

#include "cartoPersist/PictureFillSymbolPersist.h"
#include "cartoPersist/SymbolPersistCreator.h"
#include "cartoPersist/LegendGroupPersist.h"
#include <display/PictureFillSymbol.h>
#include <display/LineSymbol.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

PictureFillSymbolPersist::PictureFillSymbolPersist()
    : ISymbolPersist()
    , m_symbol(nullptr)
{

}

PictureFillSymbolPersist::PictureFillSymbolPersist(const PictureFillSymbol &symbol)
    : ISymbolPersist()
    , m_symbol(&symbol)
{
}

void PictureFillSymbolPersist::save(QJsonObject &obj)
{
    obj.insert("source", m_symbol->source());

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

ISymbolUPtr PictureFillSymbolPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "PictureFillSymbolPersist: empty object";
        return nullptr;
    }

    const QJsonValue jsonSource = obj.value("source");

    // FillSymbol
    const QJsonObject jsonOutline = obj.value("outline").toObject();

    const QString typeName = jsonOutline.value("type").toString();
    const SymbolType type = symbolTypeFromString(typeName);
    if (!verifyEnum(type))
    {
        if (error) *error = "PictureFillSymbolPersist: Invalid outline symbol type";
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

    PictureFillSymbolUPtr symbol(new PictureFillSymbol());
    symbol->setOutline(static_cast<LineSymbol*>(outlineSymbol.release()));

    if (!symbol->loadFromFile(jsonSource.toString()))
    {
        if (error) *error = QString("PictureFillSymbolPersist: can't load picture \"%1\"").arg(jsonSource.toString());
        return nullptr;
    }

    return std::move(symbol);
}
