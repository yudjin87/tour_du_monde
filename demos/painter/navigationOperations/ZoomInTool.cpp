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

#include "ZoomInTool.h"

#include <carousel/utils/IServiceLocator.h>

#include <display/RectRubberBand.h>
#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <carto/IMap.h>
#include <carto/IPainterDocument.h>
#include <carto/IPainterDocumentController.h>
#include <carousel/logging/LoggerFacade.h>

#include <QtGui/QMouseEvent>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ZoomInTool");
}

ZoomInTool::ZoomInTool()
    : ToolBase("Zoom in")
    , m_serviceLocator(nullptr)
{
    setIcon(QIcon(":/navigation/images/zoom_in.png"));
    setIconVisibleInMenu(true);
}

void ZoomInTool::execute()
{
    ToolBase::execute();
}

void ZoomInTool::initialize(IServiceLocator *serviceLocator)
{
    ToolBase::initialize(serviceLocator);

    m_serviceLocator = serviceLocator;
}

bool ZoomInTool::onMouseDown(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return false;

    IDisplay *display = m_serviceLocator->locate<IDisplay>();

    Log.d("onMouseDown");

    RectRubberBand rb;
    QRect band;
    if (!rb.newRect(display, event->pos(), &band)) {
        return false;
    }

    const bool singleClick = (band.width() <= 1) && (band.height() <= 1);
    if (singleClick) {
        changeToFixedScale();
        return false;
    }

    DisplayTransformation* transform = display->transformation();
    QRectF bounds = transform->toMapRect(band);

    Log.d(QString("New band: (%1;%2) (%3;%4)").arg(band.left()).arg(band.top()).arg(band.right()).arg(band.bottom()));
    Log.d(QString("New bandF: (%1;%2) (%3;%4)").arg(bounds.left()).arg(bounds.top()).arg(bounds.right()).arg(bounds.bottom()));

    transform->setVisibleBounds(bounds);

    IPainterDocumentController* docController = m_serviceLocator->locate<IPainterDocumentController>();
    IPainterDocument *doc = docController->document();
    IMap *map = doc->map();
    map->refresh();

    return true;
}

bool ZoomInTool::onMouseUp(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return false;

    Log.d("onMouseUp");

//    IPainterDocumentController* docController = m_serviceLocator->locate<IPainterDocumentController>();
//    IPainterDocument *doc = docController->document();
//    IMap *map = doc->map();
    //    map->refresh();

    return true;
}

void ZoomInTool::changeToFixedScale()
{
    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    display->transformation()->setScale(display->transformation()->scale() * 1.3);

    IPainterDocumentController* docController = m_serviceLocator->locate<IPainterDocumentController>();
    IPainterDocument *doc = docController->document();
    IMap *map = doc->map();
    map->refresh();
}

