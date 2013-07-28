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

#include "MenuCatalog.h"

#include <QtWidgets/QMenuBar>
#include <QtCore/QEvent>
#include <QtCore/QtAlgorithms>

//------------------------------------------------------------------------------
MenuCatalog::MenuCatalog(QMenuBar &menuBar)
    : m_menuBar(menuBar)
{
    QList<QAction *> actions = m_menuBar.actions();
    foreach(QAction *action, actions)
        installEventFilterForSubMenus(action->menu());
}

//------------------------------------------------------------------------------
MenuCatalog::~MenuCatalog()
{
    qDeleteAll(m_removedMenus);
    m_removedMenus.clear();

    qDeleteAll(m_popupMenus);
    m_popupMenus.clear();
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::addMenu(const QString &title)
{
    QMenu *menu = findMenuEverywhere(title);
    if (menu != nullptr)
        return menu;

    menu = m_menuBar.addMenu(title);
    installEventFilterForSubMenus(menu);
    onMenuAdded(menu);
    return menu;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::addMenu(const QIcon &icon, const QString &title)
{
    QMenu *menu = findMenuEverywhere(title);
    if (menu != nullptr)
        return menu;

    menu = m_menuBar.addMenu(icon, title);
    installEventFilterForSubMenus(menu);
    onMenuAdded(menu);
    return menu;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::addPopup(const QString &title)
{
    QMenu *menu = new QMenu(title);
    m_popupMenus.push_back(menu);
    installEventFilterForSubMenus(menu);
    onSubMenuAdded(menu);
    return menu;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::addPopup(const QIcon &icon, const QString &title)
{
    QMenu *menu = new QMenu(title);
    menu->setIcon(icon);
    m_popupMenus.push_back(menu);
    installEventFilterForSubMenus(menu);
    onSubMenuAdded(menu);
    return menu;
}

//------------------------------------------------------------------------------
void MenuCatalog::deleteMenu(const QString &title)
{
    QMenu *menu = findMenuEverywhere(title);
    deleteMenu(menu);
}

//------------------------------------------------------------------------------
void MenuCatalog::deleteMenu(QMenu *menu)
{
    if (menu == nullptr)
        return;

    if (m_removedMenus.removeOne(menu)) {
        delete menu;
        return;
    }

    QMenu *foundMenu = findMenu(menu->title());
    if (foundMenu == nullptr)
        return;

    m_menuBar.removeAction(foundMenu->menuAction());
    delete foundMenu;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::findMenu(const QString &title)
{
    return const_cast<QMenu *>(static_cast<const MenuCatalog &>(*this).findMenu(title));
}

//------------------------------------------------------------------------------
const QMenu *MenuCatalog::findMenu(const QString &title) const
{
    QList<QAction *> actions = m_menuBar.actions();

    foreach(QAction *action, actions) {
        if (action->text() == title)
            return action->menu();

        QMenu *foundMenu = findMenu(title, action->menu());
        if (foundMenu != nullptr)
            return foundMenu;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::findMenuEverywhere(const QString &title)
{
    return const_cast<QMenu *>(static_cast<const MenuCatalog &>(*this).findMenuEverywhere(title));
}

//------------------------------------------------------------------------------
const QMenu *MenuCatalog::findMenuEverywhere(const QString &title) const
{
    const QList<QMenu *> &allMenus = menus();

    foreach(QMenu *menu, allMenus) {
        if (menu->title() == title)
            return menu;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::findPopup(const QString &title)
{
    return const_cast<QMenu *>(static_cast<const MenuCatalog &>(*this).findPopup(title));
}

//------------------------------------------------------------------------------
const QMenu *MenuCatalog::findPopup(const QString &title) const
{
    foreach(QMenu *menu, m_popupMenus) {
        if (menu->title() == title)
            return menu;

        QMenu *foundMenu = findMenu(title, menu);
        if (foundMenu != nullptr)
            return foundMenu;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
QList<QMenu *> MenuCatalog::menus() const
{
    QList<QMenu *> menuBarMenus;

    QList<QAction *> actions = m_menuBar.actions();
    foreach(QAction *action, actions) {
        if (action->menu() != nullptr)
            menuBarMenus.push_back(action->menu());
    }

    QList<QMenu *> menusToReturn;
    menusToReturn.append(menuBarMenus);

    foreach(QMenu *menu, menuBarMenus) {
        QList<QMenu *> children = extractChildMenus(menu);
        menusToReturn.append(children);
    }

    menusToReturn.append(m_removedMenus);

    return menusToReturn;
}

//------------------------------------------------------------------------------
void MenuCatalog::removeMenu(const QString &title)
{
    QList<QAction *> actions = m_menuBar.actions();

    foreach(QAction *action, actions) {
        if (action->text() == title) {
            m_menuBar.removeAction(action);
            m_removedMenus.push_back(action->menu());
            action->menu()->removeEventFilter(this);
            onMenuRemoved(action->menu());
            return;
        }
    }
}

//------------------------------------------------------------------------------
QList<QMenu *> MenuCatalog::popups() const
{
    return m_popupMenus;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::findMenu(const QString &title, QMenu *inMenu) const
{
    if (inMenu == nullptr)
        return nullptr;

    QList<QAction *> actions = inMenu->actions();

    foreach(QAction *action, actions) {
        if (action->text() == title)
            return action->menu();

        QMenu *foundMenu = findMenu(title, action->menu());
        if (foundMenu != nullptr)
            return foundMenu;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
bool MenuCatalog::eventFilter(QObject *obj, QEvent *event)
{
    QMenu *menu = static_cast<QMenu *>(obj);

    switch (event->type())
    {
    case QEvent::ChildAdded:
        installEventFilterForSubMenus(menu);
        onSubMenuAdded(menu);
        break;
    case QEvent::ActionRemoved:
        m_removedMenus.push_back(menu);
        menu->removeEventFilter(this);
        onSubMenuRemoved(menu);
        break;
    default:
        break;
    }

    return QObject::eventFilter(obj, event);
}

//------------------------------------------------------------------------------
void MenuCatalog::onMenuAdded(QMenu *menu)
{
    emit menuAdded(menu);
}

//------------------------------------------------------------------------------
void MenuCatalog::onMenuRemoved(QMenu *menu)
{
    emit menuRemoved(menu);
}

//------------------------------------------------------------------------------
void MenuCatalog::onSubMenuAdded(QMenu *newMenu)
{
    emit subMenuAdded(newMenu);
}

//------------------------------------------------------------------------------
void MenuCatalog::onSubMenuRemoved(QMenu *menu)
{
    emit subMenuRemoved(menu);
}

//------------------------------------------------------------------------------
QList<QMenu *> MenuCatalog::extractChildMenus(QMenu *parentMenu)
{
    if (parentMenu == nullptr)
        return QList<QMenu *>();

    QList<QAction *> actions = parentMenu->actions();

    foreach(QAction *action, actions) {
        return extractChildMenus(action->menu());
    }

    return QList<QMenu *>();
}

//------------------------------------------------------------------------------
void MenuCatalog::installEventFilterForSubMenus(QMenu *menu)
{
    menu->installEventFilter(this);
    foreach(QAction *action, menu->actions()) {
        if (action->menu() != nullptr)
            installEventFilterForSubMenus(action->menu());
    }
}

//------------------------------------------------------------------------------
