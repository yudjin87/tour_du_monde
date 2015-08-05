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
#include <display/display_api.h>
#include <geometry/GeometryType.h>

#include <QtCore/QMap>
#include <QtGui/QPixmap>
#include <QtGui/QColor>

class IGeometry;
class ISymbol;

class DISPLAY_API SymbolThumbnail
{
public:
    explicit SymbolThumbnail(const int size, const int offset = 0);
    ~SymbolThumbnail();

    QPixmap createSymbolThumbnail(const ISymbol *forSymbol, Geometry::Type type) const;
    void setBackground(const QColor color);

private:
     void fillThumbnails();

private:
    const int m_size;
    const int m_offset;
    QColor m_bgColor;
    QMap<Geometry::Type, IGeometry *> m_thumbnails;
};

