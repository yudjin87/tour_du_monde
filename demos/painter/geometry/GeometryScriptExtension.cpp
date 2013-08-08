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

#include "GeometryScriptExtension.h"
#include "AbstractGeometry.h"
#include "IGeometryFactory.h"
#include "GeometryType.h"
#include "Point.h"
#include "Polycurve.h"
#include "Polygon.h"
#include "Polyline.h"
#include "Ring.h"
#include "Segment.h"

#include <components/jsscripting/IScriptingService.h>
#include <components/jsscripting/IScriptConsole.h>

#include <QtCore/QMetaType>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>

//------------------------------------------------------------------------------
Q_DECLARE_METATYPE(GeometryType)

//------------------------------------------------------------------------------
static const int AbstractGeometrytId = qRegisterMetaType<AbstractGeometry *>("AbstractGeometry *");
static const int IGeometryFactoryId = qRegisterMetaType<IGeometryFactory *>("IGeometryFactory *");
static const int PointId = qRegisterMetaType<Point *>("Point *");
static const int PolycurveId = qRegisterMetaType<Polycurve *>("Polycurve *");
static const int PolygonId = qRegisterMetaType<Polygon *>("Polygon *");
static const int PolylineId = qRegisterMetaType<Polyline *>("Polyline *");
static const int RingId = qRegisterMetaType<Ring *>("Ring *");
static const int SegmentId = qRegisterMetaType<Segment *>("Segment *");

//------------------------------------------------------------------------------
namespace
{
int registerRingList(QScriptEngine *engine)
{
    return qScriptRegisterMetaType<QList<Ring *>>(engine,
        qScriptValueFromSequence<QList<Ring *>>,
        qScriptValueToSequence<QList<Ring *>>);
}

int registerSegmentList(QScriptEngine *engine)
{
    return qScriptRegisterMetaType<QList<Segment *>>(engine,
        qScriptValueFromSequence<QList<Segment *>>,
        qScriptValueToSequence<QList<Segment *>>);
}

} // namespace

//------------------------------------------------------------------------------
GeometryScriptExtension::GeometryScriptExtension(QObject *parent)
    : QObject(parent)
{

}

//------------------------------------------------------------------------------
void GeometryScriptExtension::configureEngine(QScriptEngine *engine)
{
    int ringListId = registerRingList(engine); Q_UNUSED(ringListId);
    int segmentListId = registerSegmentList(engine); Q_UNUSED(segmentListId);
}

//------------------------------------------------------------------------------
