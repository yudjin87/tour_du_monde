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

#include "display/TextSymbol.h"

TextSymbol::TextSymbol(QObject *parent)
    : SymbolBase(parent)
    , m_size(1)
    , m_color(QColor(rand() % 255, rand() % 255, rand() % 255))
    , m_angle(0)
    , m_font("Times", 10)
    , m_text("")
{
}

TextSymbol::TextSymbol(const TextSymbol &o, QObject *parent)
    : SymbolBase(parent)
    , m_size(o.m_size)
    , m_color(o.m_color)
    , m_angle(o.m_angle)
    , m_font(o.m_font)
    , m_text(o.m_text)
{
    setParent(parent);
}

QColor TextSymbol::color() const
{
    return m_color;
}

void TextSymbol::setColor(const QColor &color)
{
    m_color = color;
}

void TextSymbol::setColor(int r, int g, int b, int a)
{
    setColor(QColor(r, g, b, a));
}

void TextSymbol::setAngle(qreal angle)
{
    if (m_angle == angle)
        return;

    m_angle = angle;
    emit angleChanged(angle);
}

void TextSymbol::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    emit fontChanged(font);
}

void TextSymbol::setText(QString text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged(text);
}

void TextSymbol::setupPainter(QPainter *painter)
{
    Q_UNUSED(painter)
}

void TextSymbol::resetPainter(QPainter *painter)
{
    Q_UNUSED(painter)
}

qreal TextSymbol::size() const
{
    return m_size;
}

void TextSymbol::setSize(qreal size)
{
    m_size = size;
}

qreal TextSymbol::angle() const
{
    return m_angle;
}

QFont TextSymbol::font() const
{
    return m_font;
}

QString TextSymbol::text() const
{
    return m_text;
}

