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

#include "carto/RendererCategory.h"
#include "carto/ILegendClass.h"

RendererCategory::RendererCategory()
    : IRendererCategory()
    , m_value()
    , m_legendClass(nullptr)
{
}

RendererCategory::RendererCategory(const QVariant &value, ILegendClass *legendClass)
    : IRendererCategory()
    , m_value(value)
    , m_legendClass(legendClass)
{
}

RendererCategory::RendererCategory(const RendererCategory &other)
    : IRendererCategory()
    , m_value(other.m_value)
    , m_legendClass(other.m_legendClass)
{
}

RendererCategory &RendererCategory::operator=(const RendererCategory &other)
{
    if (this != &other)
    {
        m_value = other.m_value;
        m_legendClass = other.m_legendClass;
    }

    return *this;
}

QVariant RendererCategory::value() const
{
    return m_value;
}

void RendererCategory::setValue(const QVariant &value)
{
    m_value = value;
}
QString RendererCategory::label() const
{
    return m_legendClass->label();
}

void RendererCategory::setLabel(const QString &label)
{
    m_legendClass->setLabel(label);
}

ISymbol *RendererCategory::symbol()
{
    return m_legendClass->symbol();
}

const ISymbol *RendererCategory::symbol() const
{
    return m_legendClass->symbol();
}

void RendererCategory::setSymbol(ISymbol *symbol)
{
    m_legendClass->setSymbol(symbol);
}

const ILegendClass *RendererCategory::legendClass() const
{
    return m_legendClass;
}

void RendererCategory::setLegendClass(ILegendClass *legendClass)
{
    m_legendClass = legendClass;
}

bool RendererCategory::match(const QVariant &value) const
{
    return m_value == value;
}

RendererCategory *RendererCategory::clone() const
{
    return new RendererCategory(*this);
}
