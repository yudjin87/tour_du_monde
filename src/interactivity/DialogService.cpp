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

#include "DialogService.h"

#include <QtCore/QDebug>
#include <QtGui/QDialog>

#include <logging/LoggerFacade.h>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("DialogService");
}

//------------------------------------------------------------------------------
DialogService::DialogService(QWidget *mainWindow, IServiceLocator *locator)
    : m_mainWindow(mainWindow)
    , m_locator(locator)
{
}

//------------------------------------------------------------------------------
DialogService::~DialogService()
{
    for(auto it = m_viewsMap.begin(); it != m_viewsMap.end(); ++it)
        delete it.value();

    m_viewsMap.clear();
}

//------------------------------------------------------------------------------
void DialogService::registerConstructor(const QString &dlgModelType, IDialogConstructor *constructor)
{
    m_viewsMap.insert(dlgModelType, constructor);
}

//------------------------------------------------------------------------------
bool DialogService::showDialogForModel(const QString &forDlgModelType, void *dlgModel) const
{
    if (!m_viewsMap.contains(forDlgModelType)) {
        Log.w(QString("The dialog with such model \"%1\" is not registered.").arg(forDlgModelType));
        return false;
    }

    IDialogConstructor *constructor = m_viewsMap.value(forDlgModelType);
    QDialog *dlg = createDialog(constructor, dlgModel);
    dlg->setAttribute(Qt::WA_DeleteOnClose);

    QDialog::DialogCode code = static_cast<QDialog::DialogCode>(dlg->exec());

    return (code == QDialog::Accepted);
}

//------------------------------------------------------------------------------
QDialog *DialogService::createDialog(IDialogConstructor *constructor, void *dlgModel) const
{
    constructor->injectServiceLocator(m_locator);
    QDialog *dlg = reinterpret_cast<QDialog *>(constructor->create(dlgModel, m_mainWindow));
    return dlg;
}

//------------------------------------------------------------------------------
