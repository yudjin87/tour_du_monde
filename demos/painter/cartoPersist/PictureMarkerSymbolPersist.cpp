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

#include "cartoPersist/PictureMarkerSymbolPersist.h"
#include "cartoPersist/LegendGroupPersist.h"
#include <display/PictureMarkerSymbol.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

PictureMarkerSymbolPersist::PictureMarkerSymbolPersist()
    : ISymbolPersist()
    , m_symbol(nullptr)
{

}

PictureMarkerSymbolPersist::PictureMarkerSymbolPersist(const PictureMarkerSymbol &symbol)
    : ISymbolPersist()
    , m_symbol(&symbol)
{
}

void PictureMarkerSymbolPersist::save(QJsonObject &obj)
{

}

ISymbolUPtr PictureMarkerSymbolPersist::load(const QJsonObject &obj, QString *error)
{
//    if (obj.isEmpty())
//    {
//        if (error) *error = "PictureMarkerSymbolPersist: empty object";
//        return nullptr;
//    }

    PictureMarkerSymbolUPtr symbol(new PictureMarkerSymbol());

    return std::move(symbol);
}

