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

#include "cartoPersist/SimpleTextSymbolPersist.h"
#include "cartoPersist/SymbolPersistCreator.h"
#include "cartoPersist/LegendGroupPersist.h"
#include <display/SimpleTextSymbol.h>
#include <display/LineSymbol.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

SimpleTextSymbolPersist::SimpleTextSymbolPersist()
    : ISymbolPersist()
    , m_symbol(nullptr)
{

}

SimpleTextSymbolPersist::SimpleTextSymbolPersist(const SimpleTextSymbol &symbol)
    : ISymbolPersist()
    , m_symbol(&symbol)
{
}

qreal m_size;
QColor m_color;
qreal m_angle;
QFont m_font;
QString m_text;

void SimpleTextSymbolPersist::save(QJsonObject &obj)
{
    // TextSymbol
    obj.insert("size", m_symbol->size());
    obj.insert("color", m_symbol->color().name());
    obj.insert("angle", m_symbol->angle());
    obj.insert("text", m_symbol->text());

    // Font
    QJsonObject jsonFont;
    jsonFont.insert("family", m_symbol->font().family());
    jsonFont.insert("style", static_cast<int>(m_symbol->font().style()));
    jsonFont.insert("weight", static_cast<int>(m_symbol->font().weight()));
    jsonFont.insert("pixelSize", m_symbol->font().pixelSize());

    obj.insert("font", jsonFont);
}

ISymbolUPtr SimpleTextSymbolPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "SimpleTextSymbolPersist: empty object";
        return nullptr;
    }

    // TextSymbol
    const QJsonValue jsonSize = obj.value("size");
    const QJsonValue jsonColor = obj.value("color");
    const QJsonValue jsonAngle = obj.value("angle");
    const QJsonValue jsonText = obj.value("text");

    // Font
    const QJsonObject jsonFont = obj.value("font").toObject();
    QFont font;
    font.setFamily(jsonFont.value("family").toString());
    font.setStyle(static_cast<QFont::Style>(jsonFont.value("style").toInt()));
    font.setWeight(static_cast<QFont::Weight>(jsonFont.value("weight").toInt()));
    font.setPixelSize(jsonFont.value("pixelSize").toInt());

    SimpleTextSymbolUPtr symbol(new SimpleTextSymbol());
    symbol->setSize(jsonSize.toDouble());
    symbol->setColor(QColor(jsonColor.toString()));
    symbol->setAngle(jsonAngle.toDouble());
    symbol->setText(jsonText.toString());
    symbol->setFont(font);

    return std::move(symbol);
}

