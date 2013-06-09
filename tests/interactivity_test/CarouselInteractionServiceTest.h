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

#ifndef CAROUSELINTERACTIONSERVICETEST_H
#define CAROUSELINTERACTIONSERVICETEST_H

#include <QtCore/QObject>

#include <carousel/utils/ServiceLocator.h>

class CarouselInteractionService;

class CarouselInteractionServiceTest : public QObject
{
    Q_OBJECT
public:
    explicit CarouselInteractionServiceTest(QObject *parent = 0);

private Q_SLOTS:
    void shouldCreateEmptyCatalogs();
    void shouldReturnEmptyToolByDefault();
    void shouldReturnEmptyInputInterceptor();
    void shouldReturnMainWindow();

    void shouldSetupInputInterceptor();
    void shouldSetupCurrentToolToInterceptor();
    void shouldNullToolAfterItsDeletion();
    void shouldNotThrowIfPreviousInterceptorIsNull();
    void shouldNotThrowIfNewInterceptorIsNull();
    void shouldDeletePreviousInputInterceptor();

    void shouldReturnDefaultConfigurationDelegate();
    void shouldSetupConfigurationDelegate();
    void shouldNotThrowIfPreviousDelegateIsNull();
    void shouldNotThrowIfNewDelegateIsNull();
    void shouldSaveUiStateWhenComponentManagerShutdDown();
    void shouldCallConfigureWhenComponentStarted();
    void shouldCallLoadUiStateWhenComponentStarted();
    void shouldConnectDelegateDeconfigureMethodWithComponentManagerSignal();
    void shouldDeletePreviousConfigurationDelegate();
    void shouldCallDeconfigureForAllComponentsWhileResetUi();
    void shouldCallConfigureForAllComponentsWhileResetUi();
    void shouldNotThrowIfConfigurationDelegateIsNullWhileResetUi();

    void shouldSetupActiveTool();
    void shouldDeactivatePreviousActiveTool();
    void shouldSetupNullToolWhenActiveIsDeactivated();
    void shouldSetupNullToInterceptorWhenActiveToolIsDeactivated();
    void shouldSetupNewlyCurrentToolToInterceptor();
    void shouldNotThrowIfPreviousActiveToolIsNull();
    void shouldNotThrowIfInterceptorIsNull();
    void shouldNotThrowIfInterceptorIsNullWhenActiveToolIsDeactivated();

private:
    ServiceLocator m_serviceLocator;
};

#endif // CAROUSELINTERACTIONSERVICETEST_H

