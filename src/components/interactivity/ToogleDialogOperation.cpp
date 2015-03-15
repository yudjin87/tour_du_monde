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

#include "ToogleDialogOperation.h"

#include <QtGui/QKeyEvent>

ToogleDialogOperation::ToogleDialogOperation(QWidget *widget)
    : Operation(widget->windowTitle())
    , m_widget(widget)
{
    setCheckable(true);
    setIconVisibleInMenu(true);
}

ToogleDialogOperation::ToogleDialogOperation(QWidget *widget, const QString &text)
    : Operation(text)
    , m_widget(widget)
{
    setCheckable(true);
    setIconVisibleInMenu(true);
}

ToogleDialogOperation::ToogleDialogOperation(QWidget *widget, const QIcon &icon)
    : Operation(icon, widget->windowTitle())
    , m_widget(widget)
{
    setCheckable(true);
    setIconVisibleInMenu(true);
}

ToogleDialogOperation::ToogleDialogOperation(QWidget *widget, const QIcon &icon, const QString &text)
    : Operation(icon, text)
    , m_widget(widget)
{
    setCheckable(true);
    setIconVisibleInMenu(true);
}

void ToogleDialogOperation::stopExecuting()
{
    m_widget->removeEventFilter(this);
    m_widget->close();
}

void ToogleDialogOperation::execute()
{
    m_widget->show();
    m_widget->installEventFilter(this);
}

bool ToogleDialogOperation::eventFilter(QObject *sender, QEvent *event)
{
    switch (event->type()) {
    case QEvent::Close:
    case QEvent::Hide:
        toggle();
        break;
    default:
        break;
    }

    return QObject::eventFilter(sender, event);
}

