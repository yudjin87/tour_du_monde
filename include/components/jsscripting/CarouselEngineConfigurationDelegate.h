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

#include <components/jsscripting/IEngineConfigurationDelegate.h>

class IServiceLocator;
class IScriptExtension;
class QScriptValue;
class QScriptContext;

/*!
 */
class JSSCRIPTING_API CarouselEngineConfigurationDelegate : public IEngineConfigurationDelegate
{
    Q_OBJECT
public:
    CarouselEngineConfigurationDelegate(IServiceLocator *locator, QObject *parent = nullptr);

public slots:
    /*!
     * @details
     */
    void configureFromComponent(IComponent *component, QScriptEngine *engine);

    void configureDefaults(QScriptEngine *engine, QString *output = nullptr);

protected:
    virtual void configureExtension(QScriptEngine *engine, IScriptExtension *extension);
    virtual void configureServiceLocator(QScriptEngine *engine, IServiceLocator *locator);
    virtual void configurePrintFunc(QScriptEngine *engine, QString *output);

private:
    Q_DISABLE_COPY(CarouselEngineConfigurationDelegate)
    static QScriptValue print(QScriptContext *context, QScriptEngine *engine, void *out);

private:
    IServiceLocator *m_locator;
};

#endif // CAROUSELENGINECONFIGURATIONDELEGATE_H
