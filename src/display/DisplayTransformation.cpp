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

#include "DisplayTransformation.h"

#include <carousel/logging/LoggerFacade.h>
#include <QtGui/QTransform>

#include <limits>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("DispTransform");
}

static const int flipY = -1;

DisplayTransformation::DisplayTransformation(QObject *parent)
    : QObject(parent)
    , m_bounds(QRectF())
    , m_deviceFrame(QRectF())
    , m_visibleBounds(QRectF())
    , m_scale(1.0)
{
}

DisplayTransformation::~DisplayTransformation()
{
}

QRectF DisplayTransformation::bounds() const
{
    return m_bounds;
}

void DisplayTransformation::setBounds(const QRectF &bounds)
{
    if (m_bounds == bounds)
        return;

    Log.d(QString("New bounds: (%1;%2) (%3;%4)")
          .arg(bounds.left())
          .arg(bounds.top())
          .arg(bounds.right())
          .arg(bounds.bottom()));

    m_bounds = bounds;
    emit boundsChanged(m_bounds);

    if (visibleBounds().isNull())
        setVisibleBounds(m_bounds);
}

QRectF DisplayTransformation::deviceFrame() const
{
    return m_deviceFrame;
}

void DisplayTransformation::setDeviceFrame(const QRectF &deviceFrame)
{
    if (m_deviceFrame == deviceFrame)
        return;

    m_deviceFrame = deviceFrame;
    emit deviceFrameChanged(m_deviceFrame);
}

double DisplayTransformation::scale() const
{
    double relY = m_deviceFrame.height() / m_visibleBounds.height();
    double relX = m_deviceFrame.width() / m_visibleBounds.width();

    return std::min(relY, relX);
}

void DisplayTransformation::setScale(double absoluteScale)
{
    double scale2 =  scale() / absoluteScale;

    setVisibleBounds(expandRect(m_visibleBounds, scale2));
}

QRectF DisplayTransformation::visibleBounds() const
{
    return m_visibleBounds;
}

void DisplayTransformation::setVisibleBounds(const QRectF &visibleBounds)
{
    if (m_visibleBounds == visibleBounds)
        return;

    Log.d(QString("New V. bounds: (%1;%2) (%3;%4)")
          .arg(visibleBounds.left())
          .arg(visibleBounds.top())
          .arg(visibleBounds.right())
          .arg(visibleBounds.bottom()));

    // TODO: Use fitted bounds (e.g. adjusted(-20, -20, 20, 20))
    m_visibleBounds = visibleBounds;

    double relY = m_deviceFrame.height() / visibleBounds.height();
    double relX = m_deviceFrame.width() / visibleBounds.width();

    if (relX > relY)
        m_visibleBounds.setWidth(m_deviceFrame.width() / scale());
    else
        m_visibleBounds.setHeight(m_deviceFrame.height() / scale());

    emit visibleBoundsChanged(m_visibleBounds);
}

QTransform DisplayTransformation::transform() const
{
    if (m_visibleBounds.height() <= 0 || m_visibleBounds.width() <= 0)
        return QTransform();

    double _scale = scale();

    qreal dx = m_visibleBounds.left();
    qreal dy = m_visibleBounds.bottom(); // top for flipping

    QTransform viewport;
    viewport.scale(_scale, _scale * flipY);
    viewport.translate(-dx, -dy);

    return viewport;
}

QPointF DisplayTransformation::toMapPoint(int x, int y) const
{
    qreal outX;
    qreal outY;
    transform().inverted().map(qreal(x), qreal(y), &outX, &outY);
    return QPointF(outX, outY);
}

QPointF DisplayTransformation::toMapPoint(const QPoint &position) const
{
    return toMapPoint(position.x(), position.y());
}

QRectF DisplayTransformation::toMapRect(const QRect &deviceRect) const
{
//    +------------------------------------+
//    | \                                  |
//    |  left;bottom                       |
//    |                                    |
//    |                                    |
//    |                                    |
//    |                                    |
//    +------------------------------------+
    QPointF topLeft = toMapPoint(deviceRect.bottomLeft());   // top for flipping
    QPointF bottomRight = toMapPoint(deviceRect.topRight()); // bottom for flipping
    return QRectF(topLeft, bottomRight);
}

QRectF DisplayTransformation::expandRect(const QRectF &extent, double scale)
{
    qreal new_left = extent.center().x() - extent.width() / 2 * scale;
    qreal left = std::max(m_bounds.left(), new_left);
    qreal new_right = new_left + extent.width() * scale;


    qreal new_top = extent.center().y() - extent.height() / 2 * scale;
    qreal top = std::max(m_bounds.top(), new_top);
    qreal new_bottom = new_top + extent.height() * scale;

    QRectF rect(left, top, extent.width() * scale, extent.height() * scale);

    // Adjust visible rect, if it faces with full bounds
    if (new_bottom > m_bounds.bottom()) {
        if (new_top <  m_bounds.top()) {
            // Move to the extent center, if visible heigh is greater then map extent
            qreal centerY = ((m_bounds.bottom() - m_bounds.top()) / 2) - rect.height() / 2;
            rect.moveBottom(m_bounds.bottom() + centerY * flipY);     // moveTop, top for flipping
        } else {
            rect.moveBottom(m_bounds.bottom());                       // moveTop, top for flipping
        }
    }

    if (new_right > m_bounds.right()) {
        if (new_left <  m_bounds.left()) {
            // Move to the extent center, if visible width is greater then map extent
            qreal centerX = ((m_bounds.right() - m_bounds.left()) / 2) - rect.width() / 2;
            rect.moveLeft(m_bounds.left() + centerX);
        } else {
            rect.moveLeft(m_bounds.left());
        }
    }

    return rect;
}

