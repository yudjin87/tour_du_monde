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

#include "AbstractLayer.h"

#include <limits.h>

AbstractLayer::AbstractLayer(QObject *parent)
    : QObject(parent)
    , m_name("")
    , m_isVisible(true)
    , m_minimumScale(INT_MIN)
    , m_maximumScale(INT_MAX)
{
}

const QString &AbstractLayer::name() const
{
    return m_name;
}

void AbstractLayer::setName(const QString &name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(this, name);
}

bool AbstractLayer::isVisible() const
{
    return m_isVisible;
}

void AbstractLayer::setVisible(bool visible)
{
    if (m_isVisible == visible)
        return;

    m_isVisible = visible;
    if (m_isVisible)
        show();
    else
        hide();

    emit visibilityChanged(this, m_isVisible);
}

double AbstractLayer::minimumScale() const
{
    return m_minimumScale;
}

double AbstractLayer::maximumScale() const
{
    return m_maximumScale;
}

void AbstractLayer::setMinimumScale(double minimumScale)
{
    m_minimumScale = minimumScale;
    emit minimumScaleChanged(this, minimumScale);
}

void AbstractLayer::setMaximumScale(double maximumScale)
{
    m_maximumScale = maximumScale;
    emit maximumScaleChanged(this, maximumScale);
}

