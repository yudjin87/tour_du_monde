/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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

#include <carto/DefaultNavigationHandler.h>
#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <carto/IMap.h>
#include <carto/ITourDeMondeDocument.h>
#include <carto/ITourDeMondeDocumentController.h>
#include <components/interactivity/InputDispatcher.h>

#include <QtGui/QMouseEvent>

DefaultNavigationHandler::DefaultNavigationHandler(IDisplay *display, ITourDeMondeDocumentController *docCtrl, QObject *parent)
    : QObject(parent)
    , BaseInputReceiver()
    , m_display(display)
    , m_docCtrl(docCtrl)
    , m_dispatcher(new InputDispatcher())
    , m_tracked(false)
{
    m_dispatcher->setReceiver(this);
    m_dispatcher->setSender(m_display->viewport());
    m_dispatcher->activate();
}

bool DefaultNavigationHandler::onMouseMove(QMouseEvent *event)
{
    BaseInputReceiver::onMouseMove(event);
    if (!m_tracked)
        return false;

    m_display->panMoveTo(event->pos());

    // let's other objects to continue with this event
    return false;
}

bool DefaultNavigationHandler::onMouseDown(QMouseEvent *event)
{
    if (event->button() != Qt::MiddleButton)
        return false;

    m_tracked = true;
    m_display->panStart(event->pos());

    // let's other objects to continue with this event
    return false;
}

bool DefaultNavigationHandler::onMouseUp(QMouseEvent *event)
{
    if (event->button() != Qt::MiddleButton)
        return false;

    m_tracked = false;
    m_display->panStop();

    ITourDeMondeDocument *doc = m_docCtrl->document();
    IMap *map = doc->map();
    map->refresh();

    // let's other objects to continue with this event
    return false;
}


