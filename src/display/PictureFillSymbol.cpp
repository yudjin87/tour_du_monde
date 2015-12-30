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

#include "display/PictureFillSymbol.h"
#include "display/ISymbolVisitor.h"

#include <geometry/Polygon.h>
#include <geometry/Point.h>
#include <geometry/Ring.h>

#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QImage>

PictureFillSymbol::PictureFillSymbol(QObject *parent)
    : FillSymbol(parent)
    , m_picture()
    , m_source()
    , m_oldBrush()
{
}

PictureFillSymbol::PictureFillSymbol(const PictureFillSymbol &o, QObject *parent)
    : FillSymbol(o, parent)
    , m_picture(o.m_picture)
    , m_source(o.m_source)
    , m_oldBrush()
{
}

void PictureFillSymbol::drawPolygon(const Polygon &polygon, QPainter &painter)
{
    QPainterPath path;
    for (const Ring *ring : polygon.rings())
    {
        QPolygonF poly;
        for (const Point* point : ring->points())
        {
            poly.push_back(QPointF(point->x(), point->y()));
        }
        path.addPolygon(poly);
    }

    painter.drawPath(path);
}

PictureFillSymbol::~PictureFillSymbol()
{
}

PictureFillSymbol *PictureFillSymbol::createFromFilePicture(const QString &filePath)
{
    std::unique_ptr<PictureFillSymbol> symbol(new PictureFillSymbol());
    if (!symbol->loadFromFile(filePath))
    {
        return nullptr;
    }

    return symbol.release();
}

SymbolType PictureFillSymbol::type() const
{
    return SymbolType::PictureFillSymbol;
}

void PictureFillSymbol::accept(ISymbolVisitor &visitor)
{
    visitor.visit(*this);
}

ISymbol* PictureFillSymbol::clone(QObject* parent) const
{
    return new PictureFillSymbol(*this, parent);
}

void PictureFillSymbol::setupPainter(QPainter *painter)
{
    FillSymbol::setupPainter(painter);

    m_oldBrush = painter->brush();

    QBrush brush(m_picture);
    brush.setMatrix(painter->matrix().inverted()); // like setCosmetic
    painter->setBrush(brush);
}

void PictureFillSymbol::resetPainter(QPainter *painter)
{
    FillSymbol::resetPainter(painter);
    painter->setBrush(m_oldBrush);
}

QPixmap PictureFillSymbol::picture() const
{
    return m_picture;
}

void PictureFillSymbol::setPicture(const QPixmap &picture)
{
    m_picture = picture;
}

bool PictureFillSymbol::loadFromFile(const QString &filePath)
{
    QPixmap pic;
    const bool result = pic.load(filePath);
    if (!result)
    {
        return false;
    }

    setPicture(pic);
    m_source = filePath;
    return true;
}

QString PictureFillSymbol::source() const
{
    return m_source;
}
