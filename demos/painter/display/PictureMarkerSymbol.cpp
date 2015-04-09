/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include "display/PictureMarkerSymbol.h"
#include "display/ISymbolVisitor.h"

#include <geometry/Point.h>

#include <QtGui/QPainter>
#include <QtGui/QImage>

PictureMarkerSymbol::PictureMarkerSymbol(QObject *parent)
    : MarkerSymbol(parent)
    , m_picture()
    , m_painterTransform()
{
}

PictureMarkerSymbol::PictureMarkerSymbol(const PictureMarkerSymbol &o, QObject *parent)
    : MarkerSymbol(o, parent)
    , m_picture(o.m_picture)
    , m_painterTransform()
{
}

PictureMarkerSymbol::~PictureMarkerSymbol()
{
}

PictureMarkerSymbol *PictureMarkerSymbol::createFromFilePicture(const QString &filePath)
{
    QPixmap pic;
    const bool result = pic.load(filePath);
    if (!result)
    {
        return nullptr;
    }

    PictureMarkerSymbol* symbol = new PictureMarkerSymbol();
    symbol->setPicture(pic);
    return symbol;
}

void PictureMarkerSymbol::accept(ISymbolVisitor &visitor)
{
    visitor.visit(*this);
}

ISymbol* PictureMarkerSymbol::clone(QObject* parent) const
{
    return new PictureMarkerSymbol(*this, parent);
}

void PictureMarkerSymbol::setupPainter(QPainter *painter)
{
    MarkerSymbol::setupPainter(painter);

    m_painterTransform = painter->transform();
    painter->setWorldMatrixEnabled(false);
}

void PictureMarkerSymbol::resetPainter(QPainter *painter)
{
    MarkerSymbol::resetPainter(painter);
    painter->setWorldMatrixEnabled(true);
}

QPixmap PictureMarkerSymbol::picture() const
{
    return m_picture;
}

void PictureMarkerSymbol::setPicture(const QPixmap &picture)
{
    m_picture = picture;
}

void PictureMarkerSymbol::drawPoint(const Point &point, QPainter &painter)
{
    const QPointF p = m_painterTransform.map(QPointF(point.x(), point.y()));
    painter.drawPixmap(p, m_picture);
}
