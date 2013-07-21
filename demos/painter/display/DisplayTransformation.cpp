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

#include "DisplayTransformation.h"

#include <QtGui/QTransform>

#include <limits>

//------------------------------------------------------------------------------
DisplayTransformation::DisplayTransformation(QObject *parent)
    : QObject(parent)
    , m_transform(new QTransform())
    , m_bounds(QRectF())
    , m_deviceFrame(QRectF())
    , m_visibleBounds(QRectF())
    , m_scale(1.0)
{
}

//------------------------------------------------------------------------------
DisplayTransformation::~DisplayTransformation()
{
    delete m_transform;
    m_transform = nullptr;
}

//------------------------------------------------------------------------------
QRectF DisplayTransformation::bounds() const
{
    return m_bounds;
}

//------------------------------------------------------------------------------
void DisplayTransformation::setBounds(const QRectF &bounds)
{
    if (m_bounds == bounds)
        return;

    m_bounds = bounds;
    emit boundsChanged(m_bounds);

    if (visibleBounds().isNull())
        setVisibleBounds(m_bounds);
}

//------------------------------------------------------------------------------
QRectF DisplayTransformation::deviceFrame() const
{
    return m_deviceFrame;
}

//------------------------------------------------------------------------------
void DisplayTransformation::setDeviceFrame(const QRectF &deviceFrame)
{
    if (m_deviceFrame == deviceFrame)
        return;

    m_deviceFrame = deviceFrame;
    emit deviceFrameChanged(m_deviceFrame);
}

//------------------------------------------------------------------------------
double DisplayTransformation::scale() const
{
    return m_scale;
}

//------------------------------------------------------------------------------
void DisplayTransformation::setScale(double scale)
{
    if (std::abs(m_scale - scale) <= std::numeric_limits<double>::epsilon())
        return;

    m_scale = scale;
    emit scaleChanged(m_scale);
}

//------------------------------------------------------------------------------
QRectF DisplayTransformation::visibleBounds() const
{
    return m_visibleBounds;
}

//------------------------------------------------------------------------------
void DisplayTransformation::setVisibleBounds(const QRectF &visibleBounds)
{
    if (m_visibleBounds == visibleBounds)
        return;

    m_visibleBounds = visibleBounds;
    emit visibleBoundsChanged(m_visibleBounds);
}

//------------------------------------------------------------------------------
QTransform DisplayTransformation::transform() const
{
    return QTransform();
}

//------------------------------------------------------------------------------
