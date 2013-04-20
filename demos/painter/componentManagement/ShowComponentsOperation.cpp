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

#include "ShowComponentsOperation.h"

#include <componentsystem/IComponent.h>
#include <componentsystem/ComponentDependencies.h>
#include <componentsystem/IComponentManager.h>
#include <componentsystemui/ComponentDefinitionsAdapter.h>

#include <interactivity/IDialogService.h>

#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QMainWindow>

//------------------------------------------------------------------------------
ShowComponentsOperation::ShowComponentsOperation()
    : Operation("Show components")
    , m_app(nullptr)
{
}

//------------------------------------------------------------------------------
void ShowComponentsOperation::execute()
{
    IServiceLocator &locator = m_app->serviceLocator();
    IComponentManager *manager = locator.locate<IComponentManager>();
    IDialogService *dialogService = locator.locate<IDialogService>();

    ComponentDefinitionsAdapter *adapter = new ComponentDefinitionsAdapter(&manager->dependencies());
    dialogService->showDialog(adapter);
}

//------------------------------------------------------------------------------
void ShowComponentsOperation::initialize(QObject *ip_startUpData)
{
    m_app = qobject_cast<AbstractApplication *>(ip_startUpData);
    if (m_app == nullptr)
        return;
}

//------------------------------------------------------------------------------
