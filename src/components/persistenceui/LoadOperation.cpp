/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#include "components/persistenceui/LoadOperation.h"
#include <carousel/utils/IServiceLocator.h>

LoadOperation::LoadOperation()
    : Operation("Open project")
    , m_serviceLocator(nullptr)
{
    setIcon(QIcon(":/persistenceui/images/load.png"));
    setIconVisibleInMenu(true);
}

void LoadOperation::execute()
{
//    IDisplay *display = m_serviceLocator->locate<IDisplay>();
//    display->transformation()->setVisibleBounds(display->transformation()->bounds());

//    IPainterDocumentController* docController = m_serviceLocator->locate<IPainterDocumentController>();
//    IPainterDocument *doc = docController->document();
//    IMap *map = doc->map();
//    map->refresh();
}

void LoadOperation::initialize(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
}
