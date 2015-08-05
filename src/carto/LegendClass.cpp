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

#include "carto/LegendClass.h"

LegendClass::LegendClass()
    : ILegendClass()
    , m_symbol(nullptr)
    , m_description()
    , m_label()
    , m_visible(true)
{
}

LegendClass::LegendClass(ISymbol *symbol)
    : ILegendClass()
    , m_symbol(symbol)
    , m_description()
    , m_label()
    , m_visible(true)
{
}

LegendClass::LegendClass(ISymbol *symbol, const QString &label)
    : ILegendClass()
    , m_symbol(symbol)
    , m_description()
    , m_label(label)
    , m_visible(true)
{
}

LegendClass::LegendClass(const LegendClass &other)
    : ILegendClass()
    , m_symbol(other.m_symbol->clone())
    , m_description(other.m_description)
    , m_label(other.m_label)
    , m_visible(other.m_visible)
{
}

LegendClass &LegendClass::operator=(const LegendClass &other)
{
    if (this == &other)
    {
        return *this;
    }

    m_symbol.reset(other.m_symbol->clone());
    m_description = other.m_description;
    m_label = other.m_label;

    return *this;
}

LegendClass::~LegendClass()
{
}

ILegendClass *LegendClass::clone() const
{
    return new LegendClass(*this);
}

QString LegendClass::description() const
{
    return m_description;
}

void LegendClass::setDescription(const QString &description)
{
    if (m_description == description)
    {
        return;
    }

    m_description = description;
    emit descriptionChanged(m_description);
}

QString LegendClass::label() const
{
    return m_label;
}

void LegendClass::setLabel(const QString &label)
{
    if (m_label == label)
    {
        return;
    }

    m_label = label;
    emit descriptionChanged(m_label);
}

bool LegendClass::isVisible() const
{
    return m_visible;
}

void LegendClass::setVisible(const bool visible)
{
    if (m_visible == visible)
    {
        return;
    }

    m_visible = visible;
    emit visibilityChanged(m_visible);
}

ISymbol *LegendClass::symbol()
{
    return m_symbol.get();
}

const ISymbol *LegendClass::symbol() const
{
    return m_symbol.get();
}

void LegendClass::setSymbol(ISymbol *symbol)
{
    m_symbol.reset(symbol);
    emit symbolChanged(symbol);
}
