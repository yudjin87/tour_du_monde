/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2013 Carousel team
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

#ifndef GEOMETRYTYPE_H
#define GEOMETRYTYPE_H

enum GeometryType
{
    GeometryNull          = 0,
    GeometryPoint         = 1,
    GeometryMultipoint    = 2,
    GeometryPolyline      = 3,
    GeometryPolygon       = 4,
    GeometryEnvelope      = 5,
    GeometryPath          = 6,
    GeometryAny           = 7,
    GeometryMultiPatch    = 9,
    GeometryRing          = 11,
    GeometryLine          = 13,
    GeometryCircularArc   = 14,
    GeometryBezier3Curve  = 15,
    GeometryEllipticArc   = 16,
    GeometryBag           = 17,
    GeometryTriangleStrip = 18,
    GeometryTriangleFan   = 19,
    GeometryRay           = 20,
    GeometrySphere        = 21
};

#endif // GEOMETRYTYPE_H
