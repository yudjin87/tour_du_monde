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
//------------------------------------------------------------------------------
DialogService::DialogService(QWidget *ip_mainWindow)
    : mp_mainWindow(ip_mainWindow)
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
void DialogService::registerConstructor(const QString &i_dlgModelType, IDialogConstructor *ip_constructor)
{
    m_viewsMap.insert(i_dlgModelType, ip_constructor);
}

//------------------------------------------------------------------------------
bool DialogService::showDialogForModel(const QString &i_forDlgModelType, void *ip_dlgModel) const
{
    if (!m_viewsMap.contains(i_forDlgModelType)) {
        qDebug(QString("The dialog with such model \"%1\" is not registered.")
               .arg(i_forDlgModelType).toUtf8());
        return false;
    }

    IDialogConstructor *p_constructor = m_viewsMap.value(i_forDlgModelType);
    QDialog *p_dlg = createDialog(p_constructor, ip_dlgModel);
    p_dlg->setAttribute(Qt::WA_DeleteOnClose);

    QDialog::DialogCode code = static_cast<QDialog::DialogCode>(p_dlg->exec());

    return (code == QDialog::Accepted);
}

//------------------------------------------------------------------------------
QDialog *DialogService::createDialog(IDialogConstructor *ip_constructor, void *ip_dlgModel) const
{
    QDialog *p_dlg = reinterpret_cast<QDialog *>(ip_constructor->create(ip_dlgModel, mp_mainWindow));
    return p_dlg;
}

//------------------------------------------------------------------------------
