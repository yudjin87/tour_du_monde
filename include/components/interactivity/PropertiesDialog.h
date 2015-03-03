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

#ifndef PROPERTIESDIALOG_H
#define PROPERTIESDIALOG_H

#include <components/interactivity/interactivity_global.h>
#include <QtWidgets/QDialog>

namespace Ui
{
class PropertiesDialog;
}

class PropertiesWidget;
class IServiceLocator;

// TODO: register in dialog service?
class INTERACTIVITY_API PropertiesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PropertiesDialog(IServiceLocator *serviceLocator, QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~PropertiesDialog();

    void installCentralWidget(PropertiesWidget *propertiesWidget);

    void accept() override;
    void reject() override;

private slots:
    void onPropertyChanged();

private:
    Ui::PropertiesDialog* m_ui;
    IServiceLocator *m_serviceLocator;
    PropertiesWidget *m_propertiesWidget;
};

#endif // PROPERTIESDIALOG_H
