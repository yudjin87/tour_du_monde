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

#include "ZoomOutCommand.h"

#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>

//------------------------------------------------------------------------------
ZoomOutCommand::ZoomOutCommand()
    : Command("Zoom out")
    , m_app(nullptr)
{
    setIcon(QIcon(":/navigation/images/zoom_out.png"));
    setIconVisibleInMenu(true);
}

//------------------------------------------------------------------------------
void ZoomOutCommand::execute()
{
    IServiceLocator &locator = m_app->serviceLocator();

    QGraphicsScene *scene = locator.locate<QGraphicsScene>();
    QGraphicsView *view = scene->views().first();
    view->scale(0.5, 0.5);
}

//------------------------------------------------------------------------------
void ZoomOutCommand::initialize(QObject *ip_startUpData)
{
    m_app = qobject_cast<AbstractApplication *>(ip_startUpData);
    if (m_app == nullptr)
        return;
}

//------------------------------------------------------------------------------
