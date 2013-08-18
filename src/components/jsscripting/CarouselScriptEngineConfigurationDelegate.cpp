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

#include "CarouselScriptEngineConfigurationDelegate.h"
#include "IOutputHandler.h"
#include "IScriptExtension.h"
#include "IScriptConsole.h"
#include "IScriptCollection.h"
#include "IScriptUnit.h"
#include "ServiceLocatorWrapper.h"

#include "prototypes/ComponentDefinitionPrototype.h"
#include "prototypes/PointClass.h"
#include "prototypes/PointFPrototype.h"
#include "prototypes/RectFPrototype.h"

#include <carousel/componentsystem/IComponent.h>
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QEventLoop>
#include <QtCore/QPoint>
#include <QtCore/QTimer>
#include <QtScript/QScriptEngine>

//------------------------------------------------------------------------------
Q_DECLARE_METATYPE(IScriptConsole *)
Q_DECLARE_METATYPE(IScriptCollection *)
Q_DECLARE_METATYPE(IScriptUnit *)
Q_DECLARE_METATYPE(QList<IScriptUnit *>)

//------------------------------------------------------------------------------
static const int IComponentDefinitionId = qRegisterMetaType<ComponentDefinition *>("ComponentDefinition *");
static const int ConstIComponentDefinitionId = qRegisterMetaType<const ComponentDefinition *>("const ComponentDefinition *");

static const int IScriptConsoleId = qRegisterMetaType<IScriptConsole *>("IScriptConsole *");
static const int IScriptCollectionId = qRegisterMetaType<IScriptCollection *>("IScriptCollection *");
static const int IScriptUnitId = qRegisterMetaType<IScriptUnit *>("IScriptUnit *");

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("CarouselScriptEngineConfigurationDelegate");

//------------------------------------------------------------------------------
int registerComponentsList(QScriptEngine *engine)
{
    return qScriptRegisterMetaType<QList<IComponent *>>(engine,
        qScriptValueFromSequence<QList<IComponent *>>,
        qScriptValueToSequence<QList<IComponent *>>);
}

//------------------------------------------------------------------------------
int registerScriptUnitList(QScriptEngine *engine)
{
    return qScriptRegisterMetaType<QList<IScriptUnit *>>(engine,
        qScriptValueFromSequence<QList<IScriptUnit *>>,
        qScriptValueToSequence<QList<IScriptUnit *>>);
}

//------------------------------------------------------------------------------
} // namespace


//------------------------------------------------------------------------------
CarouselScriptEngineConfigurationDelegate::CarouselScriptEngineConfigurationDelegate(IServiceLocator *locator, QObject *parent)
    : IScriptEngineConfigurationDelegate()
    , m_locator(locator)
{
    setParent(parent);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegate::configureFromComponent(IComponent *component, QScriptEngine *engine)
{
    IScriptExtension *scriptExtension = component->extension<IScriptExtension>();
    if (scriptExtension == nullptr) {
        Log.d(QString("Component \"%1\" does not have script extension for configuring. Skip it.").arg(component->name()));
        return;
    }

    configureExtension(engine, scriptExtension);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegate::configureDefaults(QScriptEngine *engine, IOutputHandler *output)
{
    configureServiceLocator(engine, m_locator);
    registerPrintFunc(engine, output);
    registerWaitFunc(engine);
    registerBasePrimitives(engine);
    registerComponentSystemTypes(engine);
    registerJsScriptingTypes(engine);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegate::configureExtension(QScriptEngine *engine, IScriptExtension *extension)
{
    extension->configureEngine(engine);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegate::configureServiceLocator(QScriptEngine *engine, IServiceLocator *locator)
{
    ServiceLocatorWrapper *wrapper = new ServiceLocatorWrapper(locator, engine);
    QScriptValue value = engine->newQObject(wrapper);
    engine->globalObject().setProperty("serviceLocator", value);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegate::registerPrintFunc(QScriptEngine *engine, IOutputHandler *output)
{
    QScriptValue printFunc = engine->newFunction(&CarouselScriptEngineConfigurationDelegate::print, (void *)output);
    engine->globalObject().setProperty("print", printFunc);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegate::registerWaitFunc(QScriptEngine *engine)
{
    QScriptValue waitFunc = engine->newFunction(&CarouselScriptEngineConfigurationDelegate::wait);
    engine->globalObject().setProperty("wait", waitFunc);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegate::registerComponentSystemTypes(QScriptEngine *engine)
{
    ComponentDefinitionPrototype *def = new ComponentDefinitionPrototype(engine);
    engine->setDefaultPrototype(qMetaTypeId<const ComponentDefinition *>(), engine->newQObject(def));
    engine->setDefaultPrototype(qMetaTypeId<ComponentDefinition *>(), engine->newQObject(def));

    int componentListId = registerComponentsList(engine);
    Q_UNUSED(componentListId);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegate::registerJsScriptingTypes(QScriptEngine *engine)
{
    int scriptUnitListId = registerScriptUnitList(engine);
    Q_UNUSED(scriptUnitListId);
}

//------------------------------------------------------------------------------
void CarouselScriptEngineConfigurationDelegate::registerBasePrimitives(QScriptEngine *engine)
{
    PointClass *point = new PointClass(engine);
    engine->globalObject().setProperty("QPoint", point->constructor());

    PointFPrototype *pointF = new PointFPrototype(engine);
    engine->setDefaultPrototype(qMetaTypeId<QPointF *>(), engine->newQObject(pointF));
    engine->setDefaultPrototype(qMetaTypeId<QPointF>(), engine->newQObject(pointF));

    RectFPrototype *rectF = new RectFPrototype(engine);
    engine->setDefaultPrototype(qMetaTypeId<QRectF *>(), engine->newQObject(rectF));
    engine->setDefaultPrototype(qMetaTypeId<QRectF>(), engine->newQObject(rectF));
}

//------------------------------------------------------------------------------
QScriptValue CarouselScriptEngineConfigurationDelegate::wait(QScriptContext *context, QScriptEngine *engine)
{
    if (context->argumentCount() != 1) {
        context->throwError(QScriptContext::SyntaxError, "Wrong number of arguments: wait(int) is expected");
        return engine->undefinedValue();
    }

    int milliseconds = context->argument(0).toInt32();

    QEventLoop loop;
    QTimer timer;
    timer.setInterval(milliseconds);
    QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start();
    loop.exec();

    return engine->undefinedValue();
}

//------------------------------------------------------------------------------
QScriptValue CarouselScriptEngineConfigurationDelegate::print(QScriptContext *context, QScriptEngine *engine, void *out)
{
    IOutputHandler *output = static_cast<IOutputHandler *>(out);
    if (output == nullptr)
        return engine->undefinedValue();

    QString outputMessage;
    for (int i = 0; i < context->argumentCount(); ++i) {
        if (i > 0)
            outputMessage.append(" ");
        outputMessage.append(context->argument(i).toString());
    }

    output->print(outputMessage);

    return engine->undefinedValue();
}

//------------------------------------------------------------------------------
