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

class FileComponentProviderTest : public QObject
{
    Q_OBJECT
public:
    explicit FileComponentProviderTest(QObject *parent = 0);

private Q_SLOTS:
    void shouldSetupFileName();
    void shouldNotSetupUnexistingFileName();

    void initialize_shouldReturnTrue();
    void initialize_shouldReturnFalseIfLoadingReturnsNull();
    void initialize_shouldCallLoadComponent();

    void loadComponent_shouldSetInvalidStateIfPathIsEmpty();
    void loadComponent_shouldSetDiscoveredStateIfParserReturnFalse();
    void loadComponent_shouldSetDiscoveredStateIfConstructorReturnFalse();
    void loadComponent_shouldSetParsedStateIfConstructorReturnTrueButInitializationFailed();
    void loadComponent_shouldLoadComponent();
    void loadComponent_shouldCallReadOnParser();
    void loadComponent_shouldCallConstructOnConstructor();
    void loadComponent_shouldPopulateWithComponent();
    void loadComponent_shouldNotPopulateComponentIfItsInitializationFault();

private:
    const QString definitionPath;
};

