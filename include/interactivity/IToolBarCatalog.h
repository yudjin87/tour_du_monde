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

#ifndef ITOOLBARCATALOG_H
#define ITOOLBARCATALOG_H

#include "interactivity_global.h"

#include <QtCore/QList>
#include <QtCore/qnamespace.h>
#include <QtCore/QObject>

class QAction;
class QToolBar;

/*!
 * @brief
 *   The IToolBarCatalog interface exposes members that work on the
 *   collection of application toolbars.
 * @details
 *   IToolBarCatalog knows about all the toolbars available to an application.
 *   This class allows you to add new toolbar to add operations. It is also used
 *   in Custimozation dialog.
 *   Use IInteractionService::catalogs().toolBarCatalog() to get a reference to the toolbars
 *   collection to insert operations specific to your extensions.
 */
class INTERACTIVITY_API IToolBarCatalog : public QObject
{
    Q_OBJECT
public:
    IToolBarCatalog(){}
    virtual ~IToolBarCatalog(){}

    /*!
     * @details
     *   This is an overloaded function.
     *
     *   Equivalent of calling add(Qt::TopToolBarArea, toolbar)
     */
    virtual QToolBar *add(const QString &i_title) = 0;

    /*!
     * @details
     *   Adds the toolbar with @a i_title into the specified area in this main window.
     *   The toolbar is placed at the end of the current toolbar block (i.e. line).
     *   If the main window already manages toolbar then it will only move the toolbar to area.
     *   Toolbars with epmty string are not allowed.
     *
     *   To add toolbar checkable item to the menu use MenuCatalog:
     * @code
     *   QMenu *fileMenu = menuCatalog.findMenuEverywhere(tr("File"));
     *   fileMenu->addAction(toolBarCatalog->add("MyToolbar")->toggleViewAction());
     * @endcode
     * @sa QToolBar::toggleViewAction()
     * @sa QMainWindow::addToolBar()
     * @sa IToolBarCatalog::add()
     *   Note, that toolbar catalog takes ownership of the new toolbar.
     */
    virtual QToolBar *add(Qt::ToolBarArea i_area, const QString &i_title) = 0;

    /*!
     * @details
     *   Searches for the toolbar specified by @a i_title, removes if any
     *   from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     */
    virtual void deleteToolbar(const QString &i_title) = 0;

    /*!
     * @details
     *   Removes specified toolbar from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     */
    virtual void deleteToolbar(QToolBar *toolbar) = 0;

    /*!
     * @details
     *   Searches for the toolbar specified by @a i_title
     *   in the added toolbars.
     * @return
     *   Found toolbar. Null, if there are no toolbars with such title.
     */
    virtual QToolBar *find(const QString &i_title) = 0;

    /*!
     * @details
     *   Searches for the toolbar specified by @a i_title
     *   in the added toolbars.
     * @return
     *   Found toolbar. Null, if there are no toolbars with such title.
     */
    virtual const QToolBar *find(const QString &i_title) const = 0;

    /*!
     * @details
     *   Gets list of all added toolbars.
     */
    virtual QList<QToolBar *> toolbars() const = 0;

signals:
    /*!
     * @details
     *   This signal is emitted after the toolbar was added to the
     *   catalog.
     * @sa add.
     */
    void toolbarAdded(QToolBar *toolbar);
};

#endif // ITOOLBARCATALOG_H
