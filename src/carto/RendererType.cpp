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

#include "carto/RendererType.h"

QString toString(const RendererType type)
{
    switch (type)
    {
    case RendererType::Simple:
        return "Simple";
    case RendererType::Categorized:
        return "Categorized";
    }

    return "UNKNOWN";
}


bool verifyEnum(const RendererType type)
{
    switch (type)
    {
    case RendererType::Simple:
    case RendererType::Categorized:
        return true;
    }

    return false;
}


RendererType rendererTypeFromString(const QString &name)
{
    if (name.toUpper() == QString("Simple").toUpper())
    {
        return RendererType::Simple;
    }

    if (name.toUpper() == QString("Categorized").toUpper())
    {
        return RendererType::Categorized;
    }

    return static_cast<RendererType>(-1);
}
