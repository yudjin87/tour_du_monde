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

#include "prototypes/RectFPrototype.h"

#include <QtScript/QScriptEngine>

RectFPrototype::RectFPrototype(QObject *parent)
    : QObject(parent)
{
}

qreal RectFPrototype::left() const
{
    QRectF *rect = qscriptvalue_cast<QRectF *>(thisObject());
    if (rect == nullptr)
        return 0; // TODO: throw script error: TypeError

    return rect->left();
}

qreal RectFPrototype::top() const
{
    QRectF *rect = qscriptvalue_cast<QRectF *>(thisObject());
    if (rect == nullptr)
        return 0; // TODO: throw script error: TypeError

    return rect->top();
}

qreal RectFPrototype::right() const
{
    QRectF *rect = qscriptvalue_cast<QRectF *>(thisObject());
    if (rect == nullptr)
        return 0; // TODO: throw script error: TypeError

    return rect->right();
}

qreal RectFPrototype::bottom() const
{
    QRectF *rect = qscriptvalue_cast<QRectF *>(thisObject());
    if (rect == nullptr)
        return 0; // TODO: throw script error: TypeError

    return rect->bottom();
}

QString RectFPrototype::toString()
{
    static QString pattern = "QRectF(l: %1, t: %2, r: %3, b: %4)";
    return pattern
            .arg(left())
            .arg(top())
            .arg(right())
            .arg(bottom());
}

