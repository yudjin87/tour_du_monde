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

#include "display/SymbolType.h"

QString toString(const SymbolType type)
{
    switch (type)
    {
    case SymbolType::SimpleFillSymbol:
        return "SimpleFillSymbol";
    case SymbolType::PictureFillSymbol:
        return "PictureFillSymbol";
    case SymbolType::SimpleLineSymbol:
        return "SimpleLineSymbol";
    case SymbolType::SimpleMarkerSymbol:
        return "SimpleMarkerSymbol";
    case SymbolType::PictureMarkerSymbol:
        return "PictureMarkerSymbol";
    }

    return "UNKNOWN";
}


bool verifyEnum(const SymbolType type)
{
    switch (type)
    {
    case SymbolType::SimpleFillSymbol:
    case SymbolType::PictureFillSymbol:
    case SymbolType::SimpleLineSymbol:
    case SymbolType::SimpleMarkerSymbol:
    case SymbolType::PictureMarkerSymbol:
        return true;
    }

    return false;
}


SymbolType symbolTypeFromString(const QString &name)
{
    if (name.toUpper() == QString("SimpleFillSymbol").toUpper())
    {
        return SymbolType::SimpleFillSymbol;
    }
    if (name.toUpper() == QString("PictureFillSymbol").toUpper())
    {
        return SymbolType::PictureFillSymbol;
    }
    if (name.toUpper() == QString("SimpleLineSymbol").toUpper())
    {
        return SymbolType::SimpleLineSymbol;
    }
    if (name.toUpper() == QString("SimpleMarkerSymbol").toUpper())
    {
        return SymbolType::SimpleMarkerSymbol;
    }
    if (name.toUpper() == QString("PictureMarkerSymbol").toUpper())
    {
        return SymbolType::PictureMarkerSymbol;
    }
    return static_cast<SymbolType>(-1);
}
