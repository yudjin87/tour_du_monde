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

#include "SymbolItem.h"
#include <display/SymbolThumbnail.h>
#include <QtGui/QPixmap>

SymbolItem::SymbolItem(const ISymbol *symbol, const Geometry::Type geometry)
    : QStandardItem()
    , m_symbol(symbol->clone())
    , m_geometry(geometry)
{
    Qt::ItemFlags defaultFlags = flags();
    defaultFlags &= ~Qt::ItemIsEditable;
    setFlags(defaultFlags);
}

SymbolItem::~SymbolItem()
{
}

void SymbolItem::setSymbol(const ISymbol *symbol)
{
    m_symbol.reset(symbol->clone());
    emitDataChanged();
}

QVariant SymbolItem::data(int role) const
{
    switch (role)
    {
    case Qt::DecorationRole:
        SymbolThumbnail thumbnailCreator(16, 2);
        thumbnailCreator.setBackground(Qt::white);
        QPixmap symbol = thumbnailCreator.createSymbolThumbnail(m_symbol.get(), m_geometry);
        return symbol;
    }

    return QStandardItem::data(role);
}
