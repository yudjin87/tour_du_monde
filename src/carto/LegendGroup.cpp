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

#include "carto/LegendGroup.h"

#include <algorithm>

LegendGroup::LegendGroup()
    : ILegendGroup()
    , m_legendClasses()
    , m_editable()
    , m_visible()
    , m_heading()
{
}

LegendGroup::LegendGroup(const LegendGroup &other)
    : ILegendGroup()
    , m_legendClasses()
    , m_editable(other.m_editable)
    , m_visible(other.m_visible)
    , m_heading(other.m_heading)
{
    for (const ILegendClassUPtr& legendClass : other.m_legendClasses)
    {
        m_legendClasses.emplace_back(legendClass->clone());
    }
}

LegendGroup &LegendGroup::operator=(const LegendGroup &other)
{
    if (this == &other)
    {
        return *this;
    }

    m_editable = other.m_editable;
    m_visible = other.m_visible;
    m_heading = other.m_heading;

    for (const ILegendClassUPtr& legendClass : other.m_legendClasses)
    {
        m_legendClasses.emplace_back(legendClass->clone());
    }

    return *this;
}

LegendGroup::~LegendGroup()
{
}

ILegendGroup *LegendGroup::clone() const
{
    return new LegendGroup(*this);
}

ILegendGroup::ILegendClassVector::const_iterator LegendGroup::begin() const
{
    return m_legendClasses.begin();
}

ILegendGroup::ILegendClassVector::const_iterator LegendGroup::end() const
{
    return m_legendClasses.end();
}

QString LegendGroup::heading() const
{
    return m_heading;
}

void LegendGroup::setHeading(const QString &heading)
{
    if (m_heading == heading)
    {
        return;
    }

    m_heading = heading;
    emit headingChanged(m_heading);
}

bool LegendGroup::isEditable() const
{
    return m_editable;
}

void LegendGroup::setEditable(const bool editable)
{
    if (m_editable == editable)
    {
        return;
    }

    m_editable = editable;
    emit editableChanged(m_editable);
}

bool LegendGroup::isVisible() const
{
    return m_visible;
}

void LegendGroup::setVisible(const bool visible)
{
    if (m_visible == visible)
    {
        return;
    }

    m_visible = visible;
    emit visibilityChanged(m_visible);
}

size_t LegendGroup::classCount() const
{
    return m_legendClasses.size();
}

ILegendClass *LegendGroup::getClass(const size_t index)
{
    return const_cast<ILegendClass *>(const_cast<const LegendGroup*>(this)->getClass(index));
}

const ILegendClass *LegendGroup::getClass(const size_t index) const
{
    if (m_legendClasses.size() <= index)
    {
        return nullptr;
    }

    const ILegendClassUPtr& legend = m_legendClasses[index];
    return legend.get();
}

ILegendClass *LegendGroup::getClass(const QString &label)
{
    return const_cast<ILegendClass *>(const_cast<const LegendGroup*>(this)->getClass(label));
}

const ILegendClass *LegendGroup::getClass(const QString &label) const
{
    const auto labelFinder = [label](const ILegendClassUPtr& u) { return u->label() == label; };
    const auto it = std::find_if(std::begin(m_legendClasses), std::end(m_legendClasses), labelFinder);
    if (it == std::end(m_legendClasses))
    {
        return nullptr;
    }

    const ILegendClassUPtr& legendClass = *it;
    return legendClass.get();
}

void LegendGroup::addClass(ILegendClass *legendClass)
{
    if (legendClass == nullptr)
    {
        return;
    }

    m_legendClasses.emplace_back(legendClass);
    emit classAdded(legendClass, m_legendClasses.size() - 1);
}

void LegendGroup::insertClass(const int index, ILegendClass *legendClass)
{
    Q_ASSERT(false && "Not implemeted!");
//    if (legendClass == nullptr)
//    {
//        return;
//    }

//    const size_t newIndex = ((0 < index) && (index < m_legendClasses.size()))
//            ? index
//            : -1; // append // TODO: if collection is empty, then begin() -1 will lead to crash

//    m_legendClasses.emplace(m_legendClasses.begin() + newIndex, legendClass);
//    emit classAdded(legendClass, index);
}

void LegendGroup::clearClasses()
{
    for (size_t i = 0; i < m_legendClasses.size(); ++i)
    {
        const ILegendClassUPtr& legendClass = m_legendClasses[i];
        emit classRemoved(legendClass.get(), i);
    }

    m_legendClasses.clear();
}

void LegendGroup::removeClass(ILegendClass *legendClass)
{
    const auto uPtrFinder = [=](const ILegendClassUPtr& u) { return u.get() == legendClass; };
    const auto it = std::find_if(std::begin(m_legendClasses), std::end(m_legendClasses), uPtrFinder);
    if (it == std::end(m_legendClasses))
    {
        // TODO: log
        return;
    }

    Q_ASSERT(legendClass == it->get());

    const size_t index = std::distance(std::begin(m_legendClasses), it);

    emit classRemoved(legendClass, static_cast<size_t>(index));
    m_legendClasses.erase(it);
}

ILegendClass *LegendGroup::takeClass(const int index)
{
    ILegendClass *legendClass = getClass(index);
    if (legendClass == nullptr)
    {
        return nullptr;
    }

    m_legendClasses.erase(m_legendClasses.begin() +index);

    emit classRemoved(legendClass, index);

    return legendClass;
}
