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

#include <QtGui/QMenuBar>
#include <QtCore/QEvent>
#include <QtCore/QtAlgorithms>

//------------------------------------------------------------------------------
MenuCatalog::MenuCatalog(QMenuBar &i_menuBar)
    : m_menuBar(i_menuBar)
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
QMenu *MenuCatalog::addMenu(const QString &i_title)
{
    QMenu *menu = m_menuBar.addMenu(i_title);
    installEventFilterForSubMenus(menu);
    onMenuAdded(menu);
    return menu;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::addMenu(const QIcon &i_icon, const QString &i_title)
{
    QMenu *menu = m_menuBar.addMenu(i_icon, i_title);
    installEventFilterForSubMenus(menu);
    onMenuAdded(menu);
    return menu;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::addPopup(const QString &i_title)
{
    QMenu *menu = new QMenu(i_title);
    m_popupMenus.push_back(menu);
    installEventFilterForSubMenus(menu);
    onSubMenuAdded(menu);
    return menu;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::addPopup(const QIcon &i_icon, const QString &i_title)
{
    QMenu *menu = new QMenu(i_title);
    menu->setIcon(i_icon);
    m_popupMenus.push_back(menu);
    installEventFilterForSubMenus(menu);
    onSubMenuAdded(menu);
    return menu;
}

//------------------------------------------------------------------------------
void MenuCatalog::deleteMenu(const QString &i_title)
{
    QMenu *menu = findMenuEverywhere(i_title);
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
QMenu *MenuCatalog::findMenu(const QString &i_title)
{
    return const_cast<QMenu *>(static_cast<const MenuCatalog &>(*this).findMenu(i_title));
}

//------------------------------------------------------------------------------
const QMenu *MenuCatalog::findMenu(const QString &i_title) const
{
    QList<QAction *> actions = m_menuBar.actions();

    foreach(QAction *action, actions) {
        if (action->text() == i_title)
            return action->menu();

        QMenu *foundMenu = findMenu(i_title, action->menu());
        if (foundMenu != nullptr)
            return foundMenu;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::findMenuEverywhere(const QString &i_title)
{
    return const_cast<QMenu *>(static_cast<const MenuCatalog &>(*this).findMenuEverywhere(i_title));
}

//------------------------------------------------------------------------------
const QMenu *MenuCatalog::findMenuEverywhere(const QString &i_title) const
{
    const QList<QMenu *> &allMenus = menus();

    foreach(QMenu *menu, allMenus) {
        if (menu->title() == i_title)
            return menu;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
QMenu *MenuCatalog::findPopup(const QString &i_title)
{
    return const_cast<QMenu *>(static_cast<const MenuCatalog &>(*this).findPopup(i_title));
}

//------------------------------------------------------------------------------
const QMenu *MenuCatalog::findPopup(const QString &i_title) const
{
    foreach(QMenu *menu, m_popupMenus) {
        if (menu->title() == i_title)
            return menu;

        QMenu *foundMenu = findMenu(i_title, menu);
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
        QList<QMenu *> children = _extractChildMenus(menu);
        menusToReturn.append(children);
    }

    menusToReturn.append(m_removedMenus);

    return menusToReturn;
}

//------------------------------------------------------------------------------
void MenuCatalog::removeMenu(const QString &i_title)
{
    QList<QAction *> actions = m_menuBar.actions();

    foreach(QAction *action, actions) {
        if (action->text() == i_title) {
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
QMenu *MenuCatalog::findMenu(const QString &i_title, QMenu *inMenu) const
{
    if (inMenu == nullptr)
        return nullptr;

    QList<QAction *> actions = inMenu->actions();

    foreach(QAction *action, actions) {
        if (action->text() == i_title)
            return action->menu();

        QMenu *foundMenu = findMenu(i_title, action->menu());
        if (foundMenu != nullptr)
            return foundMenu;
    }

    return nullptr;
}

//------------------------------------------------------------------------------
bool MenuCatalog::eventFilter(QObject *obj, QEvent *event)
{
    bool result = QObject::eventFilter(obj, event);
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

    return result;
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
QList<QMenu *> MenuCatalog::_extractChildMenus(QMenu *parentMenu)
{
    if (parentMenu == nullptr)
        return QList<QMenu *>();

    QList<QAction *> actions = parentMenu->actions();

    foreach(QAction *action, actions) {
        return _extractChildMenus(action->menu());
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
