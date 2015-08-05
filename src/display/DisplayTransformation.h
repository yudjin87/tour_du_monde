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

#pragma once
#include "display/display_api.h"

#include <QtCore/QObject>
#include <QtCore/QRectF>

class QTransform;

class DISPLAY_API DisplayTransformation : public QObject
{
    Q_OBJECT
    /*!
     * @details
     *   Gets or sets the full extent in world coordinates.
     *
     *   This property controls the full extent of the display. IMap::fullExtent() really
     *   stores its full extent here.
     *   In data view, IMap calculates the full extent of all the layers and automatically
     *   recalculates it whenever layers are added or removed from the IMap.
     *   Setting the bounds also sets the visibleBounds() to the same envelope if it is
     *   empty.
     */
    Q_PROPERTY(QRectF bounds READ bounds WRITE setBounds NOTIFY boundsChanged)

    /*!
     * @details
     *   Gets or sets the visible extent in device coordinates.
     *
     *   The deviceFrame is normally the full extent of the device with the origin equal to (0, 0).
     *   Output can also be directed to some rectangle on the device by specifying the rectangle
     *   as the device frame.
     *
     *   Right now setter for this property is for internal usage only, e.g. when IMap window is resized.
     */
    Q_PROPERTY(QRectF deviceFrame READ deviceFrame NOTIFY deviceFrameChanged)

    /*!
     * @details
     *   Gets or sets scale, that is the relationship between the dimensions of features on a
     *   map and the geographic objects they represent on the earth, commonly expressed as a fraction
     *   or a ratio.  A map scale of 1/100,000 or 1:100,000 means that one unit of measure on the map
     *   equals 100,000 of the same units on the earth.
     *
     *   The IMap object has a short-cut (IMap::mapScale()) directly to this property on
     *   its DisplayTransformation object.
     *
     *   Setting this property visibleBounds are changed, so visibleBoundsChanged signal emits.
     */
    Q_PROPERTY(double scale READ scale WRITE setScale)

    /*!
     * @details
     *   Gets or sets the visible extent in world coordinates.
     *
     *   This property controls the visible extent of the display. By setting this property to different
     *   extents, you will get zoom in / zoom out effects. The visibleBounds must fit within the current
     *   bounds().
     *
     *   IMap::extent() really stores its value in this property. In data view, the IMap::extent() (visibleBounds)
     *   is set the first time a layer is added to the IMap.
     *
     *   Zooming @a in or @a out changes the visibleBounds.
     *
     *   When the visibleBounds is set, it is always adjusted to match the aspect ratio the deviceFrame.
     */
    Q_PROPERTY(QRectF visibleBounds READ visibleBounds WRITE setVisibleBounds NOTIFY visibleBoundsChanged)

public:
    explicit DisplayTransformation(QObject *parent = nullptr);
    ~DisplayTransformation();
    
    QRectF bounds() const;
    void setBounds(const QRectF &bounds);

    QRectF deviceFrame() const;
    void setDeviceFrame(const QRectF &deviceFrame);

    double scale() const;
    void setScale(double absoluteScale);

    QRectF visibleBounds() const;
    void setVisibleBounds(const QRectF &visibleBounds);

    /*!
     * @details
     *   Gets a Qt transformation, based on this DisplayTransformation.
     */
    QTransform transform() const;

public slots:
    /*!
     * @details
     *   Calculates device coordinates corresponding to the map point.
     */
    //void toDevicePoint(const QPointF &mapPoint, int *x, int *y) const;

    /*!
     * @details
     *   Calculates device rectanlge corresponding to the map rectanlge.
     */
    //QRect toDeviceRect(const QRectF &mapRect) const;

    /*!
     * @details
     *   Converts an @a x;y location in device coordinates to real world coordinates.
     */
    QPointF toMapPoint(int x, int y) const;

    /*!
     * @details
     *   Converts an @a position in device coordinates to real world coordinates.
     */
    QPointF toMapPoint(const QPoint &position) const;

    /*!
     * @details
     *   Converts a device rectangle @a deviceRect in device coordinates to real
     *   world coordinates.
     */
    QRectF toMapRect(const QRect &deviceRect) const;

signals:
    void boundsChanged(const QRectF &bounds);
    void deviceFrameChanged(const QRectF &deviceFrame);
    void visibleBoundsChanged(const QRectF &visibleBounds);

private:
    QRectF expandRect(const QRectF &extent, double scale);

private:
    QRectF m_bounds;
    QRectF m_deviceFrame;
    QRectF m_visibleBounds;
    double m_scale;
};

