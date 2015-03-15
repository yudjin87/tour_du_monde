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

#include "prototypes/PointFPrototype.h"

#include <QtScript/QScriptEngine>

PointFPrototype::PointFPrototype(QObject *parent)
    : QObject(parent)
{

}

qreal PointFPrototype::x() const
{
    QPointF *point = qscriptvalue_cast<QPointF *>(thisObject());
    if (point == nullptr)
        return 0; // TODO: throw script error: TypeError

    return point->x();
}

void PointFPrototype::setX(qreal x)
{
    QPointF *point = qscriptvalue_cast<QPointF*>(thisObject());
    if (point == nullptr)
        return;

    point->setX(x);
}

qreal PointFPrototype::y() const
{
    QPointF *point = qscriptvalue_cast<QPointF*>(thisObject());
    if (point == nullptr)
        return 0;

    return point->y();
}

void PointFPrototype::setY(qreal y)
{
    QPointF *point = qscriptvalue_cast<QPointF*>(thisObject());
    if (point == nullptr)
        return;

    point->setY(y);
}

QString PointFPrototype::toString()
{
    static QString pattern = "QPointF(x: %1, y: %2)";
    return pattern
            .arg(x())
            .arg(y());
}


