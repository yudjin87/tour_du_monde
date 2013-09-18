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

#ifndef ISCRIPTEXTENSION_H
#define ISCRIPTEXTENSION_H

#include <carousel/componentsystem/IComponentExtension.h>
#include <components/jsscripting/jsscripting_global.h>

class QScriptEngine;

/*!
 * @brief
 *   This interface used by the IScriptEngineConfigurationDelegate to configure QScriptEngine
 *   by the component extension.
 * @details
 *   If some component wants to extend script with new funcitons or types, or register wrappers
 *   for some non-QObject classes, it should be a child of the JsScriptingComponent. This mean a
 *   dependency of component parent name:  @a "org.carousel.JsScripting". Then to get chance for
 *   registration, this component should also provide IScriptExtension extension. The overridden
 *   IScriptExtension::configureEngine method will be invoked every time, when QScriptEngine
 *   configuration is needed. So, in your extension you can register what ever you want in the
 *   QScriptEngine.
 *
 * @sa IComponent::extension(), IScriptEngineConfigurationDelegate
 */
class JSSCRIPTING_API IScriptExtension : public IComponentExtension
{
public:
    /*!
     * @details
     * @constructor{IScriptExtension}.
     */
    IScriptExtension(){}

    /*!
     * @details
     *   This method will be invoked every time when a new instance of the QScriptEngine
     *   is needed to be configured by other components. Usually each execution of the
     *   IScriptUnit is required a new engine.
     *
     *   Implement this method to extend an @a engine with additional functions, classes or
     *   wrappers for your types.
     *
     * @sa REGISTER_METATYPE
     */
    virtual void configureEngine(QScriptEngine *engine) = 0;

private:
    Q_DISABLE_COPY(IScriptExtension)
};

#define QUOTE_X(t) #t
#define QUOTE(t) QUOTE_X(t)
#define POINTER *
#define CONST const

/*!
 * @details
 *   A convinient macro that allows to register a @a Type pointer at the Qt meta system.
 *
 *   E.g. REGISTER_METATYPE(IScriptUnit); will produce the following code:
 * @code
 *   static const int TypeIScriptUnitId = qRegisterMetaType<IScriptUnit *>("IScriptUnit*")
 * @endcode
 */
#define REGISTER_METATYPE(Type) static const int Type##Id = qRegisterMetaType<Type *>(#Type QUOTE(POINTER)); \
    Q_UNUSED(Type##Id)

/*!
 * @details
 *   A convinient macro that allows to register a @a Type pointer at the Qt meta system.
 */
#define REGISTER_CONST_METATYPE(Type) static const int ConstType##Id = qRegisterMetaType<const Type *>(QUOTE(CONST) #Type QUOTE(POINTER))\
    Q_UNUSED(Type##Id)


#endif // ISCRIPTEXTENSION_H
