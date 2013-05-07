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

#ifndef IDOCKWINDOWCATALOG_H
#define IDOCKWINDOWCATALOG_H

#include "interactivity_global.h"

#include <QtCore/QList>
#include <QtCore/QObject>

class QDockWidget;
class QWidget;

/*!
 * @brief
 *   The IDockWidgetCatalog interface provide methods to work with
 *   dockable widgets in application.
 * @details
 *   IDockWidgetCatalog knows about all the dockable windows available to an
 *   application.
 *   This class allows you to add new dock window, and it is also used
 *   in Custimozation dialog.
 *   Use IInteractionService::catalogs().dockWidgetCatalog() to get a reference to this
 *   object to insert widgets specific to your extensions.
 *
 *   To add checkable action that can be used to show or close this dock widget
 *   to the menu use IMenuCatalog:
 * @code
 *   QMenu *windowsMenu = menuCatalog.findMenuEverywhere(tr("Windows"));
 *   windowsMenu->addAction(dockWidgetCatalog->addDockWidget(new MyWidget()));
 * @endcode
 */
class INTERACTIVITY_API IDockWidgetCatalog : public QObject
{
    Q_OBJECT
public:
    IDockWidgetCatalog(){}
    virtual ~IDockWidgetCatalog(){}

    /*!
     * @details
     *   Creates new QDockWidget, sets @a widget to it and
     *   adds new dockable widget to the main window into the
     *   left area. Null pointer will be skipped.
     *
     *   Note, that catalog takes ownership of the new
     *   dock widget.
     */
    virtual QDockWidget *addDockWidget(QWidget *widget, const QString &windowTitle = "") = 0;

    /*!
     * @details
     *   Creates new QDockWidget, sets @a widget to it and
     *   adds new dockable widget to the main window into the
     *   @a area area. Null pointer will be skipped.
     *
     *   Note, that catalog takes ownership of the new
     *   dock widget.
     */
    virtual QDockWidget *addDockWidget(QWidget *widget, const QString &windowTitle, Qt::DockWidgetArea area) = 0;

    /*!
     * @details
     *   Removes specified dockable widget from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     */
    virtual void deleteDockWidget(QDockWidget *dockWidget) = 0;

    /*!
     * @details
     *   Returns all dockable widgets added to the catalog.
     */
    virtual QList<QDockWidget *> dockWidgets() const = 0;

signals:
    /*!
     * @details
     *   This signal is emitted after the dock widget was added to the
     *   catalog.
     * @sa addDockWidget.
     */
    void dockWidgetAdded(QDockWidget *widget);
};

#endif // IDOCKWINDOWCATALOG_H
