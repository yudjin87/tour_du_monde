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
namespace Geometry
{
enum class Type
{
    Null          = 0,
    Point         = 1,
    Multipoint    = 2,
    Polyline      = 3,
    Polygon       = 4,
    Envelope      = 5,
    Path          = 6,
    Any           = 7,
    MultiPatch    = 9,
    Ring          = 11,
    Line          = 13,
    CircularArc   = 14,
    Bezier3Curve  = 15,
    EllipticArc   = 16,
    Bag           = 17,
    TriangleStrip = 18,
    TriangleFan   = 19,
    Ray           = 20,
    Sphere        = 21
};
}




