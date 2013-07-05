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
#include <QtWidgets/QDialog>

#include <carousel/logging/LoggerFacade.h>

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
    for(auto it = m_dialogMap.begin(); it != m_dialogMap.end(); ++it)
        delete it.value();

    m_dialogMap.clear();
}

//------------------------------------------------------------------------------
bool DialogService::isConstructorRegistered(const QString &forDlgModelType) const
{
    return m_dialogMap.contains(forDlgModelType);
}

//------------------------------------------------------------------------------
void DialogService::registerConstructor(const QString &dlgModelType, IDialogConstructor *constructor)
{
    m_dialogMap.add(dlgModelType, constructor);
}

//------------------------------------------------------------------------------
bool DialogService::showDialogForModel(const QString &forDlgModelType, void *dlgModel) const
{
    if (!isConstructorRegistered(forDlgModelType)) {
        Log.w(QString("The dialog with such model \"%1\" is not registered.").arg(forDlgModelType));
        return false;
    }

    QDialog *dlg = createDialogForModel(forDlgModelType, dlgModel);
    QDialog::DialogCode code = static_cast<QDialog::DialogCode>(dlg->exec());

    return (code == QDialog::Accepted);
}

//------------------------------------------------------------------------------
QDialog *DialogService::createDialogForModel(const QString &forDlgModelType, void *dlgModel) const
{
    if (!isConstructorRegistered(forDlgModelType)) {
        Log.w(QString("The dialog with such model \"%1\" is not registered.").arg(forDlgModelType));
        return nullptr;
    }

    IDialogConstructor *constructor = m_dialogMap.value(forDlgModelType)->last();

    constructor->injectServiceLocator(m_locator);
    QDialog *dlg = reinterpret_cast<QDialog *>(constructor->create(dlgModel, m_mainWindow));
    dlg->setAttribute(Qt::WA_DeleteOnClose);

    return dlg;
}

//------------------------------------------------------------------------------
bool DialogService::unregisterConstructor(const QString &forDlgModelType)
{
    if (!isConstructorRegistered(forDlgModelType))
        return false;

    QList<IDialogConstructor *> *constructors = m_dialogMap.value(forDlgModelType);

    // Pop and delete last constructor
    IDialogConstructor *constructor = constructors->last();
    delete constructor;
    constructors->removeLast();

    // Remove constructors list from the map, if last was popped
    if (constructors->empty()) {
        m_dialogMap.remove(forDlgModelType);
        delete constructors;
    }

    return true;
}

//------------------------------------------------------------------------------
