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

#ifndef MOCKCOMPONENTINITIALISER_H
#define MOCKCOMPONENTINITIALISER_H

#include <componentsystem/ComponentInitialiser.h>

#include <QtCore/QList>

class MockComponentInitialiser : public ComponentInitialiser
{
public:
    MockComponentInitialiser();
    ~MockComponentInitialiser();

    void shutdownComponent(IComponent *component);
    bool startupComponent(IComponent *component, QObject *ip_initializationData);
    void forceShutdownComponent(IComponent *component);

    IComponent *mp_shutdownComponent;
    IComponent *mp_startupComponent;
    QObject *mp_initializationData;
    QList<IComponent *> m_shutdownComponents;
    QList<IComponent *> m_forceShutdownComponents;
    QList<IComponent *> m_startupComponents;
};

#endif // MOCKCOMPONENTINITIALISER_H
