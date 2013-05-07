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

#include "MockDialogService.h"

#include <QtCore/QTimer>
#include <QtGui/QDialog>
//------------------------------------------------------------------------------
MockDialogService::MockDialogService(QWidget *mainWindow, IServiceLocator *locator)
    : DialogService(mainWindow, locator)
    , m_created_dlg(nullptr)
{
}

//------------------------------------------------------------------------------
QDialog *MockDialogService::createDialog(IDialogConstructor *constructor, void *dlgModel) const
{
    m_created_dlg = DialogService::createDialog(constructor, dlgModel);

    if (m_created_dlg->result() == QDialog::Accepted)
        QTimer::singleShot(200, m_created_dlg, SLOT(accept()));
    else
        QTimer::singleShot(200, m_created_dlg, SLOT(reject()));

    return m_created_dlg;
}

//------------------------------------------------------------------------------
