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

#ifndef DOCKWINDOWCATALOG_H
#define DOCKWINDOWCATALOG_H

#include "interactivity_global.h"
#include "IDockWidgetCatalog.h"

class QMainWindow;

/*!
 * @brief
 *   The DockWidgetCatalog class provide methods to work with
 *   dockable widgets in application.
 * @details
 *   This class allows you to add new dock window, and it is also used
 *   in Custimozation dialog.
 * @sa IDockWidgetCatalog
 */
class INTERACTIVITY_API DockWidgetCatalog : public IDockWidgetCatalog
{
    Q_OBJECT
public:
    DockWidgetCatalog(QMainWindow &i_shell);
    ~DockWidgetCatalog();

    /*!
     * @details
     *   Creates new QDockWidget, sets @a widget to it and
     *   adds new dockable widget to the main window into the
     *   left area. Null pointer will be skipped.
     *
     *   Note, that catalog takes ownership of the new
     *   dock widget.
     */
    QDockWidget *addDockWidget(QWidget *widget, const QString &windowTitle = "");

    /*!
     * @details
     *   Creates new QDockWidget, sets @a widget to it and
     *   adds new dockable widget to the main window into the
     *   @a i_area area. Null pointer will be skipped.
     *
     *   Note, that catalog takes ownership of the new
     *   dock widget.
     */
    QDockWidget *addDockWidget(QWidget *widget, const QString &windowTitle, Qt::DockWidgetArea i_area);

    /*!
     * @details
     *   Removes specified dockable widget from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     */
    void deleteDockWidget(QDockWidget *dockWidget);

    /*!
     * @details
     *   Returns all dockable widgets added to the catalog.
     */
    QList<QDockWidget *> dockWidgets() const;

protected:
    /*!
     * @details
     *   Emits a dockWidgetAdded() signal when specified one is added to
     *   catalog.
     */
    virtual void onDockWidgetAdded(QDockWidget *widget);

private:
    QList<QDockWidget *> m_widgets;
    QMainWindow &m_shell;
};

#endif // DOCKWINDOWCATALOG_H
