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

#include "cartoUI/LegendClassItem.h"
#include <display/SymbolThumbnail.h>
#include <display/ISymbol.h>
#include <QtGui/QPixmap>

LegendClassItem::LegendClassItem(const ILegendClass *legend, const Geometry::Type geometry)
    : QStandardItem()
    , m_legend(legend)
    , m_geometry(geometry)
{
    Qt::ItemFlags defaultFlags = flags();
    defaultFlags &= ~Qt::ItemIsEditable;
    setFlags(defaultFlags);

    connect(m_legend, &ILegendClass::symbolChanged, this, &LegendClassItem::onSymbolChanged);
    connect(m_legend, &ILegendClass::labelChanged, this, &LegendClassItem::onLabelChanged);
}

LegendClassItem::~LegendClassItem()
{
}

void LegendClassItem::onSymbolChanged(const ISymbol *)
{
    emitDataChanged();
}

void LegendClassItem::onLabelChanged(const QString &)
{
    emitDataChanged();
}

QVariant LegendClassItem::data(int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        return m_legend->label();
    case Qt::DecorationRole:
        SymbolThumbnail thumbnailCreator(16, 2);
        thumbnailCreator.setBackground(Qt::white);
        QPixmap legend = thumbnailCreator.createSymbolThumbnail(m_legend->symbol(), m_geometry);
        return legend;
    }

    return QStandardItem::data(role);
}
