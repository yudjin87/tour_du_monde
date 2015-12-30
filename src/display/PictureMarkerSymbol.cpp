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

#include "display/PictureMarkerSymbol.h"
#include "display/ISymbolVisitor.h"

#include <geometry/Point.h>

#include <QtGui/QPainter>
#include <QtGui/QImage>

PictureMarkerSymbol::PictureMarkerSymbol(QObject *parent)
    : MarkerSymbol(parent)
    , m_picture()
    , m_painterTransform()
    , m_source()
{
}

PictureMarkerSymbol::PictureMarkerSymbol(const PictureMarkerSymbol &o, QObject *parent)
    : MarkerSymbol(o, parent)
    , m_picture(o.m_picture)
    , m_painterTransform()
    , m_source(o.m_source)
{
}

PictureMarkerSymbol::~PictureMarkerSymbol()
{
}

PictureMarkerSymbol *PictureMarkerSymbol::createFromFilePicture(const QString &filePath)
{
    std::unique_ptr<PictureMarkerSymbol> symbol(new PictureMarkerSymbol());
    if (!symbol->loadFromFile(filePath))
    {
        return nullptr;
    }

    return symbol.release();
}

SymbolType PictureMarkerSymbol::type() const
{
    return SymbolType::PictureMarkerSymbol;
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

bool PictureMarkerSymbol::loadFromFile(const QString &filePath)
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

QString PictureMarkerSymbol::source() const
{
    return m_source;
}

void PictureMarkerSymbol::drawPoint(const Point &point, QPainter &painter)
{
    const QPointF p = m_painterTransform.map(QPointF(point.x(), point.y()));
    QRect bBox(QPoint(0, 0), m_picture.size());
    bBox.moveCenter(p.toPoint());

    painter.drawPixmap(bBox, m_picture);
}
