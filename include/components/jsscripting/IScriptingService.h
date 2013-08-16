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

#ifndef ISCRIPTINGSERVICE_H
#define ISCRIPTINGSERVICE_H

#include <components/jsscripting/jsscripting_global.h>

#include <QtCore/QObject>

class IScriptConsole;
class IScriptEngineConfigurationDelegate;
class IScriptCollection;

/*!
 * @brief
 */
class JSSCRIPTING_API IScriptingService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(IScriptCollection *scripts READ scripts)
public:
    IScriptingService(){}

    virtual IScriptConsole *console() = 0;

    virtual IScriptCollection *scripts() = 0;

    virtual IScriptEngineConfigurationDelegate *delegate() = 0;
    virtual const IScriptEngineConfigurationDelegate *delegate() const = 0;
    virtual void setDelegate(IScriptEngineConfigurationDelegate *delegate) = 0;

private:
    Q_DISABLE_COPY(IScriptingService)
};

#endif // ISCRIPTINGSERVICE_H
