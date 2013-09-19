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

#ifndef CAROUSELENGINECONFIGURATIONDELEGATE_H
#define CAROUSELENGINECONFIGURATIONDELEGATE_H

#include <components/jsscripting/IScriptEngineConfigurationDelegate.h>

class IOutputHandler;
class IServiceLocator;
class IScriptExtension;
class QScriptValue;
class QScriptContext;

/*!
 * @brief
 *   It is a default implementation of the IScriptEngineConfigurationDelegate interface.
 * @details
 *   Each time when new QScriptEngine is created to evaluate some JavaScript,
 *   this the configureFromComponent() method is invoked by the ScriptingService
 *   for each component to get it a chance to register custom types, new functions
 *   and other objects. Also it is called when new component is started at runtime.
 *
 * @sa IScriptExtension
 */
class JSSCRIPTING_API CarouselScriptEngineConfigurationDelegate : public IScriptEngineConfigurationDelegate
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{CarouselScriptEngineConfigurationDelegate} using specified @a locator for wrapping it for
     *   script.
     */
    CarouselScriptEngineConfigurationDelegate(IServiceLocator *locator, QObject *parent = nullptr);

public slots:
    /*!
     * @details
     *   Configures specified @a engine using IScriptExtension extension from the @a component.
     *   Does nothing, if component does not provide IScriptExtension.
     */
    void configureFromComponent(IComponent *component, QScriptEngine *engine);

    /*!
     * @details
     *   Configures specified @a engine with default types and functions like explore(), include() and
     *   prototype for the QPoint.
     *
     *   An @a output is a handler for the print() function. Each time when print() is invoked
     *   from the script, IOutputHandler::print() will be invoked.
     */
    void configureDefaults(QScriptEngine *engine, IOutputHandler *output = nullptr);

protected:
    virtual void configureExtension(QScriptEngine *engine, IScriptExtension *extension);
    virtual void configureServiceLocator(QScriptEngine *engine, IServiceLocator *locator);

    virtual void registerPrintFunc(QScriptEngine *engine, IOutputHandler *output);
    virtual void registerExploreFunc(QScriptEngine *engine, IOutputHandler *output);
    virtual void registerWaitFunc(QScriptEngine *engine);
    virtual void registerIncludeFunc(QScriptEngine *engine);
    virtual void registerBasePrimitives(QScriptEngine *engine);
    virtual void registerComponentSystemTypes(QScriptEngine *engine);
    virtual void registerJsScriptingTypes(QScriptEngine *engine);

private:
    Q_DISABLE_COPY(CarouselScriptEngineConfigurationDelegate)
    static QScriptValue print(QScriptContext *context, QScriptEngine *engine, void *out);
    static QScriptValue wait(QScriptContext *context, QScriptEngine *engine);
    static QScriptValue explore(QScriptContext *context, QScriptEngine *engine, void *out);
    static QScriptValue include(QScriptContext *context, QScriptEngine *engine, void *thisObj);
    static QScriptValue findValue(QScriptEngine *engine, const QString &name);

private:
    IServiceLocator *m_locator;
};

#endif // CAROUSELENGINECONFIGURATIONDELEGATE_H
