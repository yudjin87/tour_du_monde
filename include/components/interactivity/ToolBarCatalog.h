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

#ifndef TOOLBARCATALOG_H
#define TOOLBARCATALOG_H

#include "interactivity_global.h"
#include "IToolBarCatalog.h"

class QMainWindow;

/*!
 * @brief
 *   The ToolBarCatalog class exposes members that work on the
 *   collection of application toolbars.
 * @details
 *   ToolBarCatalog knows about all the toolbars available to an application.
 *   This class allows you to add new toolbar to add operations. It is also used
 *   in Custimozation dialog.
 *   Use IInteractionService::catalogs().toolBarCatalog() to get a reference to the toolbars
 *   collection to insert operations specific to your extensions.
 */
class INTERACTIVITY_API ToolBarCatalog : public IToolBarCatalog
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{MenuCatalog} with specified @a mainWindow where
     *   toolbars will be added.
     */
    ToolBarCatalog(QMainWindow &mainWindow);
    ~ToolBarCatalog();

    /*!
     * @details
     *   Adds the toolbar with @a title into the specified area in this main window.
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
    QToolBar *add(Qt::ToolBarArea area, const QString &title) override;

    /*!
     * @details
     * @overload
     *   Equivalent of calling add(Qt::TopToolBarArea, title)
     */
    QToolBar *add(const QString &title) override;

    /*!
     * @details
     *   Removes specified toolbar from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     */
    void deleteToolbar(QToolBar *toolbar) override;

    /*!
     * @details
     * @overload
     */
    void deleteToolbar(const QString &title) override;

    /*!
     * @details
     *   Searches for the toolbar specified by @a title
     *   in the added toolbars.
     * @return
     *   Found toolbar. Null, if there are no toolbars with such title.
     */
    QToolBar *find(const QString &title) override;

    /*!
     * @details
     * @overload
     */
    const QToolBar *find(const QString &title) const override;

    /*!
     * @details
     *   Gets list of all added toolbars.
     */
    QList<QToolBar *> toolbars() const override;

protected:
    /*!
     * @details
     *   Emits a toolbarAdded() signal when specified one is added to
     *   catalog.
     */
    virtual void onToolbarAdded(QToolBar *toolbar);

private:
    QToolBar *createToolbar(Qt::ToolBarArea area, const QString &title);

protected:
    QList<QToolBar *> m_toolbars;
    QMainWindow &m_mainWindow;
};

#endif // TOOLBARCATALOG_H
