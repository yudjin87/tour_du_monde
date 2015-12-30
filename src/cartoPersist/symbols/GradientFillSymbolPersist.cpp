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

#include "cartoPersist/symbols/GradientFillSymbolPersist.h"
#include "cartoPersist/symbols/SymbolPersistCreator.h"
#include "cartoPersist/legends/LegendGroupPersist.h"
#include <display/GradientFillSymbol.h>
#include <display/LineSymbol.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

GradientFillSymbolPersist::GradientFillSymbolPersist()
    : ISymbolPersist()
    , m_symbol(nullptr)
{

}

GradientFillSymbolPersist::GradientFillSymbolPersist(const GradientFillSymbol &Symbol)
    : ISymbolPersist()
    , m_symbol(&Symbol)
{
}

void GradientFillSymbolPersist::save(QJsonObject &obj)
{
    obj.insert("centralColor", m_symbol->centralColor().name());
    obj.insert("surroundColor", m_symbol->surroundColor().name());
    obj.insert("triangularBellShapeFocus", m_symbol->triangularBellShapeFocus());
    obj.insert("triangularBellShapeScale", m_symbol->triangularBellShapeScale());
    obj.insert("bellShapeFocus", m_symbol->bellShapeFocus());
    obj.insert("bellShapeScale", m_symbol->bellShapeScale());
    obj.insert("blendFactor1", m_symbol->blendFactor1());
    obj.insert("blendFactor2", m_symbol->blendFactor2());
    obj.insert("blendPosition1", m_symbol->blendPosition1());
    obj.insert("blendPosition2", m_symbol->blendPosition2());

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

ISymbolUPtr GradientFillSymbolPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "GradientFillSymbolPersist: empty object";
        return nullptr;
    }

    const QJsonValue jsonCentralColor = obj.value("centralColor");
    const QJsonValue jsonSurroundColor = obj.value("surroundColor");
    const QJsonValue jsonTriangularBellShapeFocus = obj.value("triangularBellShapeFocus");
    const QJsonValue jsonTriangularBellShapeScale = obj.value("triangularBellShapeScale");
    const QJsonValue jsonBellShapeFocus = obj.value("bellShapeFocus");
    const QJsonValue jsonBellShapeScale = obj.value("bellShapeScale");
    const QJsonValue jsonBlendFactor1 = obj.value("blendFactor1");
    const QJsonValue jsonBlendFactor2 = obj.value("blendFactor2");
    const QJsonValue jsonBlendPosition1 = obj.value("blendPosition1");
    const QJsonValue jsonBlendPosition2 = obj.value("blendPosition2");

    // FillSymbol
    const QJsonObject jsonOutline = obj.value("outline").toObject();

    const QString typeName = jsonOutline.value("type").toString();
    const SymbolType type = ::symbolTypeFromString(typeName);
    if (!verifyEnum(type))
    {
        if (error) *error = "GradientFillSymbolPersist: Invalid outline Symbol type";
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

    GradientFillSymbolUPtr symbol(new GradientFillSymbol());
    symbol->setOutline(static_cast<LineSymbol*>(outlineSymbol.release()));

    symbol->setCentralColor(QColor(jsonCentralColor.toString()));
    symbol->setSurroundColor(QColor(jsonSurroundColor.toString()));
    symbol->setTriangularBellShapeFocus(jsonTriangularBellShapeFocus.toDouble());
    symbol->setTriangularBellShapeScale(jsonTriangularBellShapeScale.toDouble());
    symbol->setBellShapeFocus(jsonBellShapeFocus.toDouble());
    symbol->setBellShapeScale(jsonBellShapeScale.toDouble());
    symbol->setBlendFactor1(jsonBlendFactor1.toDouble());
    symbol->setBlendFactor2(jsonBlendFactor2.toDouble());
    symbol->setBlendPosition1(jsonBlendPosition1.toDouble());
    symbol->setBlendPosition2(jsonBlendPosition2.toDouble());

    return std::move(symbol);
}

