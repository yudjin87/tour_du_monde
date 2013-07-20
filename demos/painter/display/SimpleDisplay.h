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

#ifndef DISPLAY_H
#define DISPLAY_H

#include "IDisplay.h"

#include <QtCore/QObject>
#include <QtWidgets/QWidget>

class QPixmap;

class SimpleDisplay :  public IDisplay
{
    Q_OBJECT
public:
    SimpleDisplay(QWidget *parent = nullptr);
    ~SimpleDisplay();

    QPainter *painter();

    QPainter *startDrawing();
    void finishDrawing(QPainter *painter);

    QRectF visibleExtent() const;

    QRectF extent() const;

    void setExtent(const QRectF& extent);

    void setVisibleExtent(const QRectF& extent);

    double scale() const;
    void setScale(double scale);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent * event);

    void scrollContentsBy(int dx, int dy);

private slots:
    void emitChanged();

signals:
    void needChange();

private:
    Q_DISABLE_COPY(SimpleDisplay)
    QTransform transform();
    int getDy(double scale);
    int getDx(double scale);
    QRectF expand(const QRectF &extent, double scale);
    void adjustScrollBars();

private:
    QRectF m_extent;
    QRectF m_visibleExtent;
    QPointF m_offset;
    QPixmap *m_pixmap;
    QPainter *m_currentPainter;
    mutable QTransform m_transform;
};
#endif // DISPLAY_H
