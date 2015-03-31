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
#include <QtCore/QObject>

class MenuCatalogTest : public QObject
{
    Q_OBJECT
public:
    explicit MenuCatalogTest(QObject *parent = 0);
    
private Q_SLOTS:
    void addMenu_shouldEmit();
    void addMenu_shouldReturnExistedOne();
    void addMenu_shouldInstallFiltersToNewMenu();
    void addPopup_shouldEmit();
    void addPopup_shouldSetupProperties();
    void addPopup_shouldAddItToList();

    void shouldEmitWhenMenuAddedToExistingMenuInMenuBar();
    void shouldEmitWhenSubMenuRemovedFromExistingMenu();

    void menus_shouldReturnFromMenuBar();
    void menus_shouldReturnBothRemovedAndExistedMenus();

    void removeMenu_shouldRemoveFromMenuBar();
    void removeMenu_shouldEmitWhenRemovingFromMenuBar();

    void findMenu_shouldFindMenuFromMenuBar();
    void findMenu_shouldFindMenuFromSubmenu();
    void findMenuEverywhere_shouldFindEverywhere();
    void findPopup_shouldFindPopup();
    void findPopup_shouldFindFromSubmenu();

    void deleteMenu_shouldDeleteMenu();
    void deleteMenu_shouldDeleteRemovedMenu();
    void deleteMenu_shouldDeleteMenuByName();
};

