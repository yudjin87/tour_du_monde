/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
 * Authors:
 *   Eugene Chuguy <eugene.chuguy@gmail.com>
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

#include "Polycurve.h"
#include "Ring.h"

//------------------------------------------------------------------------------
Polycurve::Polycurve(QObject *parent)
    : AbstractGeometry(parent)
    , m_rings()
{
}

//------------------------------------------------------------------------------
Polycurve::Polycurve(const QRectF &extent, QObject *parent)
    : AbstractGeometry(extent, parent)
    , m_rings()
{
}

//------------------------------------------------------------------------------
#ifdef Q_COMPILER_INITIALIZER_LISTS
Polycurve::Polycurve(std::initializer_list<QPointF> points, QObject *parent)
    : AbstractGeometry(parent)
    , m_rings()
{
    m_rings.append(new Ring(points));
}
#else
Polycurve::Polycurve(QVector<QPointF> points, QObject *parent)
    : AbstractGeometry(parent)
    , m_rings()
{
    m_rings.append(new Ring(points));
}
#endif // #ifdef Q_COMPILER_INITIALIZER_LISTS

//------------------------------------------------------------------------------
Polycurve::~Polycurve()
{
    clearData();
}

//------------------------------------------------------------------------------
RingList &Polycurve::rings()
{
    return m_rings;
}

//------------------------------------------------------------------------------
const RingList &Polycurve::rings() const
{
    return m_rings;
}

//------------------------------------------------------------------------------
void Polycurve::clearData()
{
    foreach(Ring *ring, m_rings)
        delete ring;

    m_rings.clear();
}

//------------------------------------------------------------------------------
