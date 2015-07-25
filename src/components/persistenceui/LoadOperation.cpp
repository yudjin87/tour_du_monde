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
#include <components/persistence/IPersistenceService.h>
#include <carousel/utils/IServiceLocator.h>
#include <carousel/commands/IUndoStack.h>
#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QFileInfo>
#include <QtCore/QSettings>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMainWindow>

namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("LoadOperation");
}

LoadOperation::LoadOperation()
    : Operation("Open project")
    , m_serviceLocator(nullptr)
{
    setIcon(QIcon(":/persistenceui/images/load.png"));
    setIconVisibleInMenu(true);
}

void LoadOperation::execute()
{
    QFileDialog fileDialog(m_serviceLocator->locate<QMainWindow>(), "Load project");
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    if (!fileDialog.exec())
    {
        Log.d("Loading was canceled by user");
        return;
    }

    const QFileInfo opennedFile = fileDialog.selectedFiles().first();

    IPersistenceService* persistenceService = m_serviceLocator->locate<IPersistenceService>();
    bool result = persistenceService->load(opennedFile.absoluteFilePath());
    Q_UNUSED(result); // TODO: check
    IUndoStack *undoStack = m_serviceLocator->locate<IUndoStack>();
    undoStack->cleanIndex();
}

void LoadOperation::initialize(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
}
