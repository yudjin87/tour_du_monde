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

#ifndef ISCRIPTENGINECONFIGURATIONDELEGATE_H
#define ISCRIPTENGINECONFIGURATIONDELEGATE_H

#include <components/jsscripting/jsscripting_global.h>

#include <QtCore/QObject>

class IComponent;
class IOutputHandler;
class QScriptEngine;

/*!
 * @brief
 *   This interface used by the IScriptingService to configure QScriptEngine
 *   by the custom component extensions.
 * @details
 *   Each time when new QScriptEngine is created to evaluate some JavaScript,
 *   this the configureFromComponent() method is invoked by the ScriptingService
 *   for each component to get it a chance to register custom types, new functions
 *   and other objects. Also it is called when new component is started at runtime.
 *
 * @sa IScriptExtension
 */
class JSSCRIPTING_API IScriptEngineConfigurationDelegate : public QObject
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{IScriptEngineConfigurationDelegate}.
     */
    IScriptEngineConfigurationDelegate(){}

public slots:
    /*!
     * @details
     *   Configures specified @a engine using IScriptExtension extension from the @a component.
     *   Does nothing, if component does not provide IScriptExtension.
     */
    virtual void configureFromComponent(IComponent *component, QScriptEngine *engine) = 0;

    /*!
     * @details
     *   Configures specified @a engine with default types and functions like explore() and
     *   prototype for the QPoint.
     *
     *   An @a output is a handler for the print() function. Each time when print() is invoked
     *   from the script, IOutputHandler::print() will be invoked.
     */
    virtual void configureDefaults(QScriptEngine *engine, IOutputHandler *output = nullptr) = 0;

private:
    Q_DISABLE_COPY(IScriptEngineConfigurationDelegate)
};

#endif // ISCRIPTENGINECONFIGURATIONDELEGATE_H
