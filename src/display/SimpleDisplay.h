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
#include <display/IDisplay.h>
#include <QtCore/QMutex>
#include <QtCore/QVector>

class SimpleDisplay :  public IDisplay
{
    Q_OBJECT
public:
    SimpleDisplay(QObject *parent = nullptr);
    ~SimpleDisplay();

    void startDrawing(const DispayCache inCache) override;
    void finishDrawing(const DispayCache inCache) override;

    QPixmap &lockPixmap(const DispayCache inCache) override;
    void unlockPixmap(const DispayCache inCache) override;

    DisplayTransformation *transformation() override;
    const DisplayTransformation *transformation() const override;

    void panMoveTo(const QPoint &screenPoint) override;
    void panStart(const QPoint &screenPoint) override;
    QRectF panStop() override;

    void postDrawingTask(IDrawingTaskPtr task) override;
    QPixmapPtr createPixmap(const QColor &fillColor = Qt::transparent) const override;

    void drawOut(QPainter* toPainter) const override;

    QObject* attachedWidget() const override;
    void setAttachedWidget(QObject* attachedWidget) override;

protected:
    bool isReady() const;

private slots:
    void onVisibleBoundChanged(const QRectF &visibleBounds);
    void onDeviceFrameChanged(const QRectF &deviceFrame);

private:
    Q_DISABLE_COPY(SimpleDisplay)
    void dumpDraft(const DispayCache inCache);
    void moveVisibleBounds(int dx, int dy);
    int getDy(double scale);
    int getDx(double scale);

private:
    bool m_initialized;
    bool m_moveVisibleBound;
    bool m_wasDrawing;
    QMetaObject::Connection m_conn;
    QPointF m_offset;
    QPoint m_startPan;
    DisplayTransformation *m_transform;
    QPixmapPtr m_pixmap;
    QVector<QPixmapPtr> m_draftPixmaps;
    QObject* m_attachedWidget;

    mutable QMutex m_pixmapMutex;
};
