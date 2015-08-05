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

#include "TourDeMondeDocument.h"
#include "IMap.h"

TourDeMondeDocument::TourDeMondeDocument()
    : m_name("New Tour De Monde")
    , m_map(nullptr)
{
}

TourDeMondeDocument::~TourDeMondeDocument()
{
    delete m_map;
    m_map = nullptr;
}

IMap *TourDeMondeDocument::map()
{
    return m_map;
}

const IMap *TourDeMondeDocument::map() const
{
    return m_map;
}

void TourDeMondeDocument::addMap(IMap *map)
{
    m_map = map;
}

const QString &TourDeMondeDocument::name() const
{
    return m_name;
}

void TourDeMondeDocument::setName(const QString &name)
{
    if (m_name == name)
    {
        return;
    }

    m_name = name;
    emit nameChanged(name);
}
