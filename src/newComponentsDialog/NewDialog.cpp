/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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

#include "NewDialog.h"

#include <QtCore/QUrl>
#include <QtGui/QDesktopServices>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>

NewDialog::NewDialog(ComponentDefinitionsModel *model, QWidget *parent)
    : ComponentsDialog(model, parent)
{
    QPushButton *installButton = new QPushButton(this);
    installButton->setObjectName("installButton");
    installButton->setText("Open components directory");

    QHBoxLayout *horizontalLayout = findChild<QHBoxLayout *>("horizontalLayout");
    horizontalLayout->insertWidget(2, installButton);

    connect(installButton, &QPushButton::clicked, this, &NewDialog::onOpenComponentsDirectory);
}

void NewDialog::onOpenComponentsDirectory(bool) const
{
    // TODO: should be obtained from the app settings
    QDesktopServices::openUrl(QUrl::fromLocalFile(QApplication::applicationDirPath() + "/installedComponents"));
}

