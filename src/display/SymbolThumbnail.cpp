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

#include "display/SymbolThumbnail.h"
#include "display/ISymbol.h"

#include <geometry/IGeometry.h>
#include <geometry/Point.h>
#include <geometry/Polygon.h>
#include <geometry/Polyline.h>

#include <QtGui/QPainter>

SymbolThumbnail::SymbolThumbnail(const int size, const int offset)
    : m_size(size)
    , m_offset(offset)
    , m_bgColor(Qt::transparent)
    , m_thumbnails()
{
    fillThumbnails();
}

SymbolThumbnail::~SymbolThumbnail()
{
}

void SymbolThumbnail::setBackground(const QColor color)
{
    m_bgColor = color;
}

QPixmap SymbolThumbnail::createSymbolThumbnail(const ISymbol *forSymbol, const Geometry::Type type) const
{
    QPixmap pixmap(m_size, m_size);
    pixmap.fill(m_bgColor);
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing); // TODO: add to settings

    IGeometry *geometry = m_thumbnails[type];

    ISymbolUPtr symbol(forSymbol->clone());
    symbol->setupPainter(&painter);
    symbol->draw(geometry, &painter);
    symbol->resetPainter(&painter);

    return pixmap;
}

void SymbolThumbnail::fillThumbnails()
{
    // •
    m_thumbnails.insert(Geometry::Type::Point, new Point(m_size / 2, m_size / 2));

    // ─<
    m_thumbnails.insert(Geometry::Type::Polyline, new Polyline{
                   QPointF(m_offset, m_size / 2), QPointF(m_size / 2 + m_offset, m_size / 2),
                   QPointF(m_size / 2 + m_offset, m_size / 2), QPointF(m_size - m_offset, m_size - m_offset * 2),
                   QPointF(m_size / 2 + m_offset, m_size / 2), QPointF(m_size - m_offset, m_offset * 2)
               });

    // ■
    const QRectF rect(QPointF(m_offset, m_offset),  QPointF(m_size - m_offset - 1, m_size - m_offset - 1));
    m_thumbnails.insert(Geometry::Type::Polygon, new Polygon{rect.topLeft(), rect.topRight(), rect.bottomRight(), rect.bottomLeft()});
}

