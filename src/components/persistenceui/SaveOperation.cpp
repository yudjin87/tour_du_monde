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

#include "components/persistenceui/SaveOperation.h"
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
static LoggerFacade Log = LoggerFacade::createLogger("SaveOperation");
}

SaveOperation::SaveOperation()
    : Operation("Save project")
    , m_serviceLocator(nullptr)
{
    setIcon(QIcon(":/persistenceui/images/save.png"));
    setIconVisibleInMenu(true);
}

void SaveOperation::execute()
{
    IPersistenceService* persistenceService = m_serviceLocator->locate<IPersistenceService>();
    QFileInfo currentFile = persistenceService->absoluteFilePath();
    if (!currentFile.exists())
    {
        Log.d(QString("File \"%1\" doesn't exist, ask for a new one").arg(currentFile.absoluteFilePath()));
        QFileDialog fileDialog(m_serviceLocator->locate<QMainWindow>(), "Save project");
        fileDialog.setAcceptMode(QFileDialog::AcceptSave);
        if (!fileDialog.exec())
        {
            Log.d("Saving was canceled by user");
            return;
        }

        currentFile = fileDialog.selectedFiles().first();
    }

    bool result = persistenceService->saveAs(currentFile.absoluteFilePath());
    if (!result)
    {
        return;
    }

    IUndoStack *undoStack = m_serviceLocator->locate<IUndoStack>();
    undoStack->setClean();
}

void SaveOperation::initialize(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;

    IUndoStack *undoStack = m_serviceLocator->locate<IUndoStack>();
    setEnabled(!undoStack->isClean());
    connect(undoStack, &IUndoStack::cleanChanged, this, [this](bool clean){this->setEnabled(!clean);});
}
