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

#include "InteractiveExtension.h"
#include "ShapesWidget.h"
#include "ShapesModel.h"

#include <dom/IPainterDocument.h>
#include <dom/IPainterDocumentController.h>
#include <framework/AbstractApplication.h>
#include <interactivity/ICatalogs.h>
#include <interactivity/IDockWidgetCatalog.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QDockWidget>

InteractiveExtension::InteractiveExtension(QObject *parent /*= nullptr*/)
{
    setParent(parent);
}

void InteractiveExtension::configureGui(ICatalogs &i_inCatalogs, AbstractApplication &i_application)
{
    IPainterDocumentController* docController = i_application.serviceLocator().locate<IPainterDocumentController>();
    IPainterDocument *doc = docController->document();

    //i_inCatalogs.dockWidgetCatalog().addDockWidget(new ShapesWidget(new ShapesModel(doc->shapes().shapes())), "Shapes widget");
}

