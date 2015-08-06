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

#include "ZoomOutOperation.h"

#include <carousel/utils/IServiceLocator.h>

#include <display/IDisplay.h>
#include <display/DisplayTransformation.h>
#include <carto/IMap.h>
#include <carto/ITourDuMondeDocument.h>
#include <carto/ITourDuMondeDocumentController.h>

ZoomOutOperation::ZoomOutOperation()
    : Operation("Zoom out")
    , m_serviceLocator(nullptr)
{
    setIcon(QIcon(":/navigation/images/zoom_out.png"));
    setIconVisibleInMenu(true);
}

void ZoomOutOperation::execute()
{
    IDisplay *display = m_serviceLocator->locate<IDisplay>();
    display->transformation()->setScale(display->transformation()->scale() / 1.3);

    ITourDuMondeDocumentController* docController = m_serviceLocator->locate<ITourDuMondeDocumentController>();
    ITourDuMondeDocument *doc = docController->document();
    IMap *map = doc->map();
    map->refresh();
}

void ZoomOutOperation::initialize(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
}

