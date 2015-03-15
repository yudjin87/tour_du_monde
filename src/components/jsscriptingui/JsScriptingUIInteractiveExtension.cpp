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

#include "JsScriptingUIInteractiveExtension.h"
#include "CodeHighlighter.h"
#include "ColorTheme.h"
#include "ScriptConsoleView.h"
#include "ShowScriptsOperation.h"

#include <components/jsscripting/IScriptConsole.h>
#include <components/jsscripting/IScriptingService.h>
#include <components/interactivity/ICatalogs.h>
#include <components/interactivity/IDockWidgetCatalog.h>
#include <components/interactivity/IMenuCatalog.h>
#include <components/interactivity/IOperationCatalog.h>
#include <components/interactivity/ToggleActionWrapper.h>
#include <components/interactivity/ToogleDialogOperation.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>

JsScriptingUIInteractiveExtension::JsScriptingUIInteractiveExtension(QObject *parent /*= nullptr*/)
    : QObject(parent)
{
}

void JsScriptingUIInteractiveExtension::configureGui(ICatalogs &inCatalogs, IServiceLocator *serviceLocator)
{
    IScriptingService *service = serviceLocator->locate<IScriptingService>();
    IScriptConsole *console = service->console();
    CodeHighlighter *hilighter = new CodeHighlighter(ColorTheme::getDefault(), this);

    IDockWidgetCatalog &catalog = inCatalogs.dockWidgetCatalog();

    // script console
    QDockWidget *scriptConsoleDock = catalog.addDockWidget(
            new ScriptConsoleView(console, hilighter), "Script console", Qt::BottomDockWidgetArea);

    Operation *scriptConsole = new ToggleActionWrapper(scriptConsoleDock->toggleViewAction(), QIcon(":/jsscriptingui/images/scriptWindow.png"));
    inCatalogs.operationCatalog().add(scriptConsole);
    QMenu *viewMenu = inCatalogs.menuCatalog().addMenu("View");
    viewMenu->addAction(scriptConsole);

    // script IDE
    Operation *scriptManager = new ShowScriptsOperation();
    inCatalogs.operationCatalog().add(scriptManager);
    viewMenu->addAction(scriptManager);
}

