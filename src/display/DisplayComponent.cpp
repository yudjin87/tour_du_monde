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

#include <display/DisplayComponent.h>
#include <display/SimpleDisplay.h>
#include <display/DisplayScriptExtension.h>
#include <display/MultithreadDisplay.h>

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentExport.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QMainWindow>

static const QByteArray productName("Display");

DisplayComponent::DisplayComponent(QObject *parent)
    : BaseComponent("org.carousel.demos.Display", parent)
{
    IScriptExtension *scriptExtension = new DisplayScriptExtension(this);
    registerExtension<IScriptExtension>(scriptExtension);

    addParent("org.carousel.QmlScripting", 1, 0);
    addParent("org.carousel.Interactivity", 1, 0);
    addParent("org.carousel.demos.Geometry", 1, 0);
    setShortName("Display");
    setProductName(productName);
    setProvider("Carousel");
    setVersion(1, 0);
}

DisplayComponent::~DisplayComponent()
{
}

void DisplayComponent::onShutdown(IServiceLocator *serviceLocator)
{
    IDisplay *display = serviceLocator->unregisterInstance<IDisplay>();
    delete display;
}

bool DisplayComponent::onStartup(IServiceLocator *serviceLocator)
{
    //IDisplay *display = new SimpleDisplay(mainWindow); // TODO: settings
    IDisplay *display = new MultithreadDisplay();
    serviceLocator->registerInstance<IDisplay>(display);

    return true;
}

EXPORT_COMPONENT(DisplayComponent)

