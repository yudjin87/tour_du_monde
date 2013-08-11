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

#ifndef POINTPROTOTYPE_H
#define POINTPROTOTYPE_H

#include <QtCore/QPoint>
#include <QtCore/QObject>
#include <QtScript/QScriptable>

class PointPrototype : public QObject, public QScriptable
{
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX)
    Q_PROPERTY(int y READ y WRITE setY)
public:
    PointPrototype(QObject *parent = nullptr);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

public slots:
   QString toString();
};

Q_DECLARE_METATYPE(QPoint *)
Q_DECLARE_METATYPE(QPoint)

#endif // POINTPROTOTYPE_H
