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

#include "CarouselComponentConfigurationDelegate.h"

#include "Operation.h"
#include "ConfigurationChanges.h"
#include "ICatalogs.h"
#include "IOperationCatalog.h"
#include "IDockWidgetCatalog.h"
#include "IInteractiveExtension.h"
#include "IMenuCatalog.h"
#include "IToolBarCatalog.h"

#include <componentsystem/IComponent.h>

#include <QtGui/QAction>
#include <QtGui/QMenu>

//------------------------------------------------------------------------------
CarouselComponentConfigurationDelegate::CarouselComponentConfigurationDelegate()
    : m_changes()
{
}

//------------------------------------------------------------------------------
CarouselComponentConfigurationDelegate::~CarouselComponentConfigurationDelegate()
{
    for (auto it = m_changes.begin(); it != m_changes.end(); ++it) {
        ConfigurationChanges *ch = *it;
        delete ch;
    }

    m_changes.clear();
}

//------------------------------------------------------------------------------
void CarouselComponentConfigurationDelegate::configure(IComponent *ip_component, ICatalogs &catalogs, AbstractApplication &i_application)
{
    IInteractiveExtension *p_interactiveExtension = ip_component->extension<IInteractiveExtension>();
    if (p_interactiveExtension == nullptr)
        return;

    // Connect to the catalog changes
    ConfigurationChanges *changes = new ConfigurationChanges();
    changes->connect(&catalogs.operationCatalog(), SIGNAL(operationAdded(Operation *)),
                     SLOT(insertAddedOperation(Operation *)));

    changes->connect(&catalogs.dockWidgetCatalog(), SIGNAL(dockWidgetAdded(QDockWidget *)),
                     SLOT(insertAddedDockWidget(QDockWidget *)));

    changes->connect(&catalogs.menuCatalog(), SIGNAL(menuAdded(QMenu *)),
                     SLOT(insertAddedMenu(QMenu *)));

    changes->connect(&catalogs.menuCatalog(), SIGNAL(menuRemoved(QMenu*)),
                     SLOT(insertRemovedMenu(QMenu *)));

    changes->connect(&catalogs.toolBarCatalog(), SIGNAL(toolbarAdded(QToolBar*)),
                     SLOT(insertAddedToolbar(QToolBar *)));

// TODO: implement me!
//    changes->connect(&catalogs.menuCatalog(), SIGNAL(subMenuAdded(QAction*)),
//                     SLOT(insertInsertedOperation(QAction *)));

    m_changes.insert(ip_component, changes);

    // Configure the new component
    p_interactiveExtension->configureGui(catalogs, i_application);

    // Disconnect from the catalogs
    catalogs.operationCatalog().disconnect(changes);
    catalogs.dockWidgetCatalog().disconnect(changes);
    catalogs.menuCatalog().disconnect(changes);
    catalogs.toolBarCatalog().disconnect(changes);
}

//------------------------------------------------------------------------------
void CarouselComponentConfigurationDelegate::deconfigure(IComponent * ip_component, ICatalogs &catalogs)
{
    IInteractiveExtension *p_interactiveExtension = ip_component->extension<IInteractiveExtension>();
    if (p_interactiveExtension == nullptr)
        return;

    const ConfigurationChanges *changes = changesByComponent(ip_component);

    // Deleting inserted operations from the widgets
    // TODO: implement me!

    // Deleting added toolbars
    foreach(QToolBar *toolbar, changes->addedToolbars())
        catalogs.toolBarCatalog().deleteToolbar(toolbar);

    // Deleting added dockable widgets
    foreach(QDockWidget *dockWidget, changes->addedDockWidgets())
        catalogs.dockWidgetCatalog().deleteDockWidget(dockWidget);

    // Deleting added to the menu bar menus
    foreach(QMenu *menu, changes->addedMenus())
        catalogs.menuCatalog().deleteMenu(menu);

    // Deleting added operations at the end, after they have been
    // removed from the wigdets
    foreach(Operation *operation, changes->addedOperations())
        catalogs.operationCatalog().deleteOperation(operation);

}

//------------------------------------------------------------------------------
const ConfigurationChanges *CarouselComponentConfigurationDelegate::changesByComponent(IComponent *ip_component) const
{
    return m_changes[ip_component];
}

//------------------------------------------------------------------------------
