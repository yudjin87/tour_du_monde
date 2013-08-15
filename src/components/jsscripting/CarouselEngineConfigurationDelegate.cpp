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

#include "CarouselEngineConfigurationDelegate.h"
#include "IScriptExtension.h"
#include "ServiceLocatorWrapper.h"

#include "prototypes/ComponentDefinitionPrototype.h"
#include "prototypes/PointClass.h"
#include "prototypes/PointFPrototype.h"
#include "prototypes/RectFPrototype.h"

#include <carousel/componentsystem/IComponent.h>
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QPoint>
#include <QtScript/QScriptEngine>

//------------------------------------------------------------------------------
static const int IComponentDefinitionId = qRegisterMetaType<ComponentDefinition *>("ComponentDefinition *");
static const int ConstIComponentDefinitionId = qRegisterMetaType<const ComponentDefinition *>("const ComponentDefinition *");

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("CarouselEngineConfigurationDelegate");

//------------------------------------------------------------------------------
int registerComponentsList(QScriptEngine *engine)
{
    return qScriptRegisterMetaType<QList<IComponent *>>(engine,
        qScriptValueFromSequence<QList<IComponent *>>,
        qScriptValueToSequence<QList<IComponent *>>);
}
} // namespace


//------------------------------------------------------------------------------
CarouselEngineConfigurationDelegate::CarouselEngineConfigurationDelegate(IServiceLocator *locator, QObject *parent)
    : IEngineConfigurationDelegate()
    , m_locator(locator)
{
    setParent(parent);
}

//------------------------------------------------------------------------------
void CarouselEngineConfigurationDelegate::configureFromComponent(IComponent *component, QScriptEngine *engine)
{
    IScriptExtension *scriptExtension = component->extension<IScriptExtension>();
    if (scriptExtension == nullptr) {
        Log.d(QString("Component \"%1\" does not have script extension for configuring. Skip it.").arg(component->name()));
        return;
    }

    configureExtension(engine, scriptExtension);
}

//------------------------------------------------------------------------------
void CarouselEngineConfigurationDelegate::configureDefaults(QScriptEngine *engine, QString *output)
{
    configureServiceLocator(engine, m_locator);
    configurePrintFunc(engine, output);
    registerBasePrimitives(engine);
    registerComponentSystemPrototypes(engine);
    registerIComponentsList(engine);
}

//------------------------------------------------------------------------------
void CarouselEngineConfigurationDelegate::configureExtension(QScriptEngine *engine, IScriptExtension *extension)
{
    extension->configureEngine(engine);
}

//------------------------------------------------------------------------------
void CarouselEngineConfigurationDelegate::configureServiceLocator(QScriptEngine *engine, IServiceLocator *locator)
{
    ServiceLocatorWrapper *wrapper = new ServiceLocatorWrapper(locator, engine);
    QScriptValue value = engine->newQObject(wrapper);
    engine->globalObject().setProperty("serviceLocator", value);
}

//------------------------------------------------------------------------------
void CarouselEngineConfigurationDelegate::configurePrintFunc(QScriptEngine *engine, QString *output)
{
    QScriptValue printFunc = engine->newFunction(&CarouselEngineConfigurationDelegate::print, (void *)output);
    engine->globalObject().setProperty("print", printFunc);
}

//------------------------------------------------------------------------------
void CarouselEngineConfigurationDelegate::registerComponentSystemPrototypes(QScriptEngine *engine)
{
    ComponentDefinitionPrototype *def = new ComponentDefinitionPrototype(engine);
    engine->setDefaultPrototype(qMetaTypeId<const ComponentDefinition *>(), engine->newQObject(def));
    engine->setDefaultPrototype(qMetaTypeId<ComponentDefinition *>(), engine->newQObject(def));
}

//------------------------------------------------------------------------------
void CarouselEngineConfigurationDelegate::registerBasePrimitives(QScriptEngine *engine)
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
void CarouselEngineConfigurationDelegate::registerIComponentsList(QScriptEngine *engine)
{
    int componentListId = registerComponentsList(engine);
    Q_UNUSED(componentListId);
}

//------------------------------------------------------------------------------
QScriptValue CarouselEngineConfigurationDelegate::print(QScriptContext *context, QScriptEngine *engine, void *out)
{
    QString *output = static_cast<QString *>(out);
    if (output == nullptr)
        return engine->undefinedValue();

    for (int i = 0; i < context->argumentCount(); ++i) {
        if (i > 0)
            output->append(" ");
        output->append(context->argument(i).toString());
    }

    output->append("\n");

    return engine->undefinedValue();
}

//------------------------------------------------------------------------------
