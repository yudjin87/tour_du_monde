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

#ifndef IMENUCATALOG_H
#define IMENUCATALOG_H

#include "interactivity_global.h"

#include <QtCore/QList>
#include <QtCore/QObject>

class QIcon;
class QMenu;
class QMenuBar;
class QString;

/*!
 * @brief
 *   The IMenuCatalog interface provides access to members that work on the
 *   collection of application menus.
 * @details
 *   IMenuCatalog knows about collection of all the menus available to an application.
 *   This interface allows you to add new menu to the main bar or to the inner menu
 *   found by its title. It is also used
 *   in Custimozation dialog.
 *   Use IInteractionService::catalogs().menuCatalog() to get a reference to the menus collection
 *   to insert operations specific to your extensions.
 */
class INTERACTIVITY_API IMenuCatalog : public QObject
{
    Q_OBJECT
public:
    IMenuCatalog(){}
    virtual ~IMenuCatalog(){}

    /*!
     * @details
     *   Appends a new QMenu with @a i_title to the menu bar. The menu bar takes ownership of the menu.
     *   Returns the new menu.
     *
     *   To add menu item to the menu use OperationCatalog:
     * @code
     *   QMenu *fileMenu = menuCatalog.findMenuEverywhere(tr("File"));
     *   fileMenu->addAction(operationCatalog->add(new MyPrintOperation()));
     * @endcode
     * @sa OperationCatalog::register();
     */
    virtual QMenu *addMenu(const QString &i_title) = 0;

    /*!
     * @details
     *   Appends a new QMenu with @a i_icon and @a i_title to the menu bar.
     *   The menu bar takes ownership of the menu.
     *   Returns the new menu.
     */
    virtual QMenu *addMenu(const QIcon &i_icon, const QString &i_title) = 0;

    /*!
     * @details
     *   Adds a new QMenu with @a i_title to the catalog (it takes ownership of the menu).
     *   You can use this menu later for the popup, using findPopup().
     *   Returns the new menu.
     */
    virtual QMenu *addPopup(const QString &i_title) = 0;

    /*!
     * @details
     *   Adds a new QMenu with @a i_icon and @a i_title to the catalog
     *   (it takes ownership of the menu).
     *   You can use this menu later for the popup, using findPopup().
     *   Returns the new menu.
     */
    virtual QMenu *addPopup(const QIcon &i_icon, const QString &i_title) = 0;

    /*!
     * @details
     *   Searches for the menu specified by @a i_title, removes if any
     *   from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     *
     *   To remove menu from menu bar without deleting use removeMenu().
     */
    virtual void deleteMenu(const QString &i_title) = 0;

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
    virtual void deleteMenu(QMenu *menu) = 0;

    /*!
     * @details
     *   Searches for the menu specified by @a i_title
     *   in the menu bar and other menus.
     * @return
     *   Found menu. Null, if there are no menus with such title.
     */
    virtual QMenu *findMenu(const QString &i_title)  = 0;

    /*!
     * @details
     *   Searches for the menu specified by @a i_title
     *   in the menu bar and other menus.
     * @return
     *   Found menu. Null, if there are no menus with such title.
     */
    virtual const QMenu *findMenu(const QString &i_title) const  = 0;

    /*!
     * @details
     *   Searches for the menu specified by @a i_title
     *   in the menu bar, other menus and in removed menus list.
     * @return
     *   Found menu. Null, if there are no menus with such title.
     */
    virtual QMenu *findMenuEverywhere(const QString &i_title)  = 0;

    /*!
     * @details
     *   Searches for the menu specified by @a i_title
     *   in the menu bar, other menus and in removed menus list.
     * @return
     *   Found menu. Null, if there are no menus with such title.
     */
    virtual const QMenu *findMenuEverywhere(const QString &i_title) const  = 0;

    /*!
     * @details
     *   Searches for the popup menu specified by @a i_title.
     * @return
     *   Found menu. Null, if there are no popup menus with such title.
     */
    virtual QMenu *findPopup(const QString &i_title)  = 0;

    /*!
     * @details
     *   Searches for the popup menu specified by @a i_title.
     * @return
     *   Found menu. Null, if there are no popup menus with such title.
     */
    virtual const QMenu *findPopup(const QString &i_title) const  = 0;

    /*!
     * @details
     *   Returns all menus, found in the menu bar, other menus and
     *   in removed menus list.
     */
    virtual QList<QMenu *> menus() const = 0;

    /*!
     * @details
     *   Removes QMenu with @a i_title from the menu bar and
     *   stores it in its internal collection.
     *   The menu catalog takes ownership of the removed menu.
     *
     *   To remove menu item from the menu use QMenu::removeAction().
     */
    virtual void removeMenu(const QString &i_title) = 0;

    /*!
     * @details
     *   Returns all popups menus, registered in the catalog.
     */
    virtual QList<QMenu *> popups() const = 0;

signals:
    /*!
     * @details
     *   This signal is emitted after menu was added to the
     *   main menu.
     * @sa addMenu.
     */
    void menuAdded(QMenu *menu);

    /*!
     * @details
     *   This signal is emitted after menu was removed from the
     *   main menu.
     * @sa removeMenu.
     */
    void menuRemoved(QMenu *menu);

    /*!
     * @details
     *   This signal is emitted after menu was added to the
     *   existed menus as submenu.
     * @sa QMenu::addMenu(), addPopup.
     */
    void subMenuAdded(QMenu *menu);

    /*!
     * @details
     *   This signal is emitted after menu was removed from the
     *   existed added menus.
     * @sa QWidget::removeAction().
     */
    void subMenuRemoved(QMenu *menu);
};

#endif // IMENUCATALOG_H
