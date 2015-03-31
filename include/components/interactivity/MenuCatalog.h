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

#pragma once
#include "interactivity_global.h"
#include "IMenuCatalog.h"

/*!
 * @brief
 *   The MenuCatalog class provides access to members that work on the
 *   collection of application menus.
 * @details
 *   MenuCatalog knows about collection of all the menus available to an application.
 *   This class allows you to add new menu to the main bar or to the inner menu
 *   found by its title. It is also used
 *   in Custimozation dialog.
 *   Use IInteractionService::catalogs().menuCatalog() to get a reference to the menus collection
 *   to insert operations specific to your extensions.
 */
class INTERACTIVITY_API MenuCatalog : public IMenuCatalog
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{MenuCatalog} with specified @a menuBar where
     *   menus will be added.
     */
    MenuCatalog(QMenuBar &menuBar);
    ~MenuCatalog();

    /*!
     * @details
     *   Appends a new QMenu with @a title to the menu bar. The menu bar takes ownership of the menu.
     *   Returns the new menu.
     *
     *   To add menu item to the menu use OperationCatalog:
     * @code
     *   QMenu *fileMenu = menuCatalog.findMenuEverywhere(tr("File"));
     *   fileMenu->addAction(operationCatalog->add(new MyPrintOperation()));
     * @endcode
     * @sa OperationCatalog::register();
     */
    QMenu *addMenu(const QString &title) override;

    /*!
     * @details
     *   Appends a new QMenu with @a icon and @a title to the menu bar.
     *   The menu bar takes ownership of the menu.
     *   Returns the new menu.
     */
    QMenu *addMenu(const QIcon &icon, const QString &title) override;

    /*!
     * @details
     *   Adds a new QMenu with @a title to the catalog (it takes ownership of the menu).
     *   You can use this menu later for the popup, using findPopup().
     *   Returns the new menu.
     */
    QMenu *addPopup(const QString &title) override;

    /*!
     * @details
     *   Adds a new QMenu with @a icon and @a title to the catalog
     *   (it takes ownership of the menu).
     *   You can use this menu later for the popup, using findPopup().
     *   Returns the new menu.
     */
    QMenu *addPopup(const QIcon &icon, const QString &title) override;

    /*!
     * @details
     *   Searches for the menu specified by @a title, removes if any
     *   from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     *
     *   To remove menu from menu bar without deleting use removeMenu().
     */
    void deleteMenu(const QString &title) override;

    /*!
     * @details
     *   Removes specified menu from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     *
     *   To remove menu from menu bar without deleting use removeMenu().
     */
     void deleteMenu(QMenu *menu) override;

    /*!
     * @details
     *   Searches for the menu specified by @a title
     *   in the menu bar and other menus.
     * @return
     *   Found menu. Null, if there are no menus with such title.
     */
    QMenu *findMenu(const QString &title) override;

    /*!
     * @details
     *   Searches for the menu specified by @a title
     *   in the menu bar and other menus.
     * @return
     *   Found menu. Null, if there are no menus with such title.
     */
    const QMenu *findMenu(const QString &title) const override;

    /*!
     * @details
     *   Searches for the menu specified by @a title
     *   in the menu bar, other menus and in removed menus list.
     * @return
     *   Found menu. Null, if there are no menus with such title.
     */
    QMenu *findMenuEverywhere(const QString &title) override;

    /*!
     * @details
     *   Searches for the menu specified by @a title
     *   in the menu bar, other menus and in removed menus list.
     * @return
     *   Found menu. Null, if there are no menus with such title.
     */
    const QMenu *findMenuEverywhere(const QString &title) const override;

    /*!
     * @details
     *   Searches for the popup menu specified by @a title.
     * @return
     *   Found menu. Null, if there are no popup menus with such title.
     */
    QMenu *findPopup(const QString &title) override;

    /*!
     * @details
     *   Searches for the popup menu specified by @a title.
     * @return
     *   Found menu. Null, if there are no popup menus with such title.
     */
    const QMenu *findPopup(const QString &title) const override;

    /*!
     * @details
     *   Returns all menus, found in the menu bar, other menus and
     *   in removed menus list.
     */
    QList<QMenu *> menus() const override;

    /*!
     * @details
     *   Removes QMenu with @a title from the menu bar and
     *   stores it in its internal collection.
     *   The menu catalog takes ownership of the removed menu.
     *
     *   To remove menu item from the menu use QMenu::removeAction().
     */
    void removeMenu(const QString &title) override;

    /*!
     * @details
     *   Returns all popups menus, registered in the catalog.
     */
    QList<QMenu *> popups() const override;

    /*!
     * @details
     *   MenuCatalog installs itself as QObject's event filter to
     *   handle menus adding and removing.
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

protected:
    /*!
     * @details
     *   Searches for the menu specified by @a title
     *   in the @a inMenu and its childer menus.
     * @return
     *   Found menu. Null, if there are no menus with such title.
     */
    QMenu *findMenu(const QString &title, QMenu *inMenu) const;

    /*!
     * @details
     *   Emits a menuAdded() signal when menu is added to the
     *   main menu.
     */
    virtual void onMenuAdded(QMenu *menu);

    /*!
     * @details
     *   Emits a menuAdded() signal when menu is removed from the
     *   main menu.
     */
    virtual void onMenuRemoved(QMenu *menu);

    /*!
     * @details
     *   Emits a subMenuAdded() signal when specified menu is added to
     *   existed menu.
     */
    virtual void onSubMenuAdded(QMenu *newMenu);

    /*!
     * @details
     *   Emits a subMenuRemoved() signal when menu is removed from
     *   existed menu.
     */
    virtual void onSubMenuRemoved(QMenu *menu);

private:
    static QList<QMenu *> extractChildMenus(QMenu *parentMenu);
    void installEventFilterForSubMenus(QMenu *menu);

private:
    QMenuBar &m_menuBar;
    QList<QMenu *> m_removedMenus;
    QList<QMenu *> m_popupMenus;
};

