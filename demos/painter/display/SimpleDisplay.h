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

class SimpleDisplay :  public IDisplay
{
    Q_OBJECT
public:
    SimpleDisplay(QWidget *parent = nullptr);
    ~SimpleDisplay();

    QPixmap *startDrawing() override;
    void finishDrawing(QPixmap *pixmap) override;

    DisplayTransformation *transformation() override;
    const DisplayTransformation *transformation() const override;

    void panMoveTo(const QPoint &screenPoint) override;
    void panStart(const QPoint &screenPoint) override;
    QRectF panStop() override;
    void updateWindow() override;

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent * event) override;

    void scrollContentsBy(int dx, int dy) override;

signals:
    void needChange();

private slots:
    void emitChanged();
    void onVisibleBoundChanged(const QRectF &visibleBounds);

private:
    Q_DISABLE_COPY(SimpleDisplay)
    void moveVisibleBounds(int dx, int dy);
    int getDy(double scale);
    int getDx(double scale);
    void adjustScrollBars();

private:
    bool m_moveVisibleBound;
    QMetaObject::Connection m_conn;
    QPointF m_offset;
    QPoint m_startPan;
    QPixmap *m_pixmap;
    DisplayTransformation *m_transform;
};
#endif // DISPLAY_H
