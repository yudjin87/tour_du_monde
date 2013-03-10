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

#ifndef MENUCATALOGTEST_H
#define MENUCATALOGTEST_H

#include <QtCore/QObject>

class MenuCatalogTest : public QObject
{
    Q_OBJECT
public:
    explicit MenuCatalogTest(QObject *parent = 0);
    
private Q_SLOTS:
    void shouldReturnExistedMenus();
    void shouldReturnBothRemovedAndExistedMenus();

    void shouldEmitWhenMenuAddedToMenuBar();
    void shouldEmitWhenMenuAddedToExistingMenu();
    void shouldEmitWhenMenuAddedToExistingMenuInMenuBar();
    void shouldEmitWhenPopupAdded();

    void shouldEmitWhenMenuRemovedFromMenuBar();
    void shouldEmitWhenSubMenuRemovedFromExistingMenu();

    void shouldRemoveMenuFromMenuBar();

    void shouldFindMenuFromMenuBar();
    void shouldFindMenuFromSubmenu();
    void shouldFindMenuEverywhere();
    
    void shouldCreatePopupMenu();
    void shouldAddPopupMenuToList();
    void shouldFindPopup();
    void shouldFindPopupFromSubmenu();

    void shouldDeleteMenu();
    void shouldDeleteRemovedMenu();
    void shouldDeleteMenuByName();
};

#endif // MENUCATALOGTEST_H
