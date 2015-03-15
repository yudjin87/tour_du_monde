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

#include <QtScript/QScriptEngine>
#include "prototypes/PointClass.h"
#include "prototypes/PointPrototype.h"

Q_DECLARE_METATYPE(PointClass*)

PointClass::PointClass(QScriptEngine* engine)
    : QObject(engine)
    , QScriptClass(engine)
{
    qScriptRegisterMetaType<QPoint>(engine, toScriptValue, fromScriptValue);
    m_proto = engine->newQObject(new PointPrototype(this),
                                QScriptEngine::ScriptOwnership,
                                QScriptEngine::SkipMethodsInEnumeration
                                | QScriptEngine::ExcludeSuperClassMethods
                                | QScriptEngine::ExcludeSuperClassProperties);
    const QScriptValue& global = engine->globalObject();
    m_proto.setPrototype(global.property("Object").property("prototype"));
    m_ctor = engine->newFunction(construct, m_proto);
    m_ctor.setData(engine->toScriptValue(this));
}

PointClass::~PointClass()
{
}

QString PointClass::name() const
{
    return QLatin1String("QPoint");
}

QScriptValue PointClass::prototype() const
{
    return m_proto;
}

QScriptValue PointClass::constructor()
{
    return m_ctor;
}

QScriptValue PointClass::construct(QScriptContext* ctx, QScriptEngine*)
{
    PointClass* cls = qscriptvalue_cast<PointClass*>(ctx->callee().data());
    if (!cls)
        return QScriptValue();

    switch (ctx->argumentCount()) {
    case 0: // QPoint()
        return cls->newInstance();
    case 1: // QPoint(const QPoint&)
    {
        const QScriptValue& arg = ctx->argument(0);
        if (arg.instanceOf(ctx->callee())) // QColor(const QColor&)
            return cls->newInstance(qscriptvalue_cast<QPoint>(arg));
        return QScriptValue::UndefinedValue;
        break;
    }
    case 2: // QPoint(qreal x, qreal y)
    {
        const QScriptValue& x = ctx->argument(0);
        const QScriptValue& y = ctx->argument(1);
        return cls->newInstance(QPoint(x.toNumber(), y.toNumber()));
    }
    }

    // TODO: throw an exception
    return cls->newInstance();
}

QScriptValue PointClass::toScriptValue(QScriptEngine* eng, const QPoint& p)
{
    const QScriptValue& ctor = eng->globalObject().property("QPoint");
    PointClass* cls = qscriptvalue_cast<PointClass*>(ctor.data());
    if (!cls)
        return eng->newVariant(QVariant::fromValue(p));

    return cls->newInstance(p);
}

void PointClass::fromScriptValue(const QScriptValue& obj, QPoint& p)
{
    p = qvariant_cast<QPoint>(obj.data().toVariant());
}

QScriptValue PointClass::newInstance()
{
    return newInstance(QPoint());
}

QScriptValue PointClass::newInstance(const QPoint& p)
{
    QScriptValue data = engine()->newVariant(QVariant::fromValue(p));
    return engine()->newObject(this, data);
}

