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

#ifndef POINTCLASS_H
#define POINTCLASS_H

#include <QtCore/QObject>
#include <QtCore/QPoint>

#include <QtScript/QScriptClass>

class QScriptEngine;
class QScriptContext;

class PointClass : public QObject, public QScriptClass
{
    Q_OBJECT
public:
    PointClass(QScriptEngine* engine = nullptr);
    ~PointClass();

    QScriptValue constructor();
    QScriptValue newInstance();
    QScriptValue newInstance(const QPoint&);
    QString name() const;
    QScriptValue prototype() const;

private:
    static QScriptValue construct(QScriptContext* ctx, QScriptEngine* eng);
    static QScriptValue toScriptValue(QScriptEngine* eng, const QPoint&);
    static void fromScriptValue(const QScriptValue& obj, QPoint&);

    QScriptValue m_proto;
    QScriptValue m_ctor;
};

#endif // POINTCLASS_H
