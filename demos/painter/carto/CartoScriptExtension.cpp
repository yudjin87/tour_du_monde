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

#include "CartoScriptExtension.h"
#include "AbstractLayer.h"
#include "IPainterDocumentController.h"
#include "IPainterDocument.h"
#include "IMap.h"

#include <components/jsscripting/IScriptingService.h>
#include <components/jsscripting/IScriptConsole.h>

#include <QtCore/QMetaType>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValueIterator>

//------------------------------------------------------------------------------
Q_DECLARE_METATYPE(IPainterDocument *)
Q_DECLARE_METATYPE(IPainterDocumentController *)
Q_DECLARE_METATYPE(IMap *)
Q_DECLARE_METATYPE(QList<AbstractLayer *>)

//------------------------------------------------------------------------------
namespace
{
int registerScriptMetaTypes(QScriptEngine *engine)
{
    return qScriptRegisterMetaType<QList<AbstractLayer *>>(engine,
        qScriptValueFromSequence<QList<AbstractLayer *>>,
        qScriptValueToSequence<QList<AbstractLayer *>>);
}
} // namespace

//------------------------------------------------------------------------------
CartoScriptExtension::CartoScriptExtension(QObject *parent)
    : QObject(parent)
{

}

//------------------------------------------------------------------------------
void CartoScriptExtension::configureEngine(IServiceLocator *locator, QScriptEngine *engine)
{
    int cartoTypeIds = registerScriptMetaTypes(engine);
    Q_UNUSED(cartoTypeIds);

    REGISTER_METATYPE(IPainterDocument);
    REGISTER_METATYPE(IMap);
}

//------------------------------------------------------------------------------
