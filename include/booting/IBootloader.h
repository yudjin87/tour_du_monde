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
#ifndef IBOOTLOADER_H
#define IBOOTLOADER_H

#include "booting/booting_global.h"

#include <QtCore/QObject>

class IServiceLocator;

/*!
 * @brief
 *   The abstract IBootloader class provides a basic bootstrapping sequence and hooks
 *   that specific implementations can override.
 * @details
 *   After bootloading process the configured IServiceLocator is available through
 *   serviceLocator() method. Later it will be injected to the all components and other
 *   elements during their start or initialization. It is needed to register/locate to
 *   common services and your components' services.
 */
class BOOTING_API IBootloader : public QObject
{
    Q_OBJECT
public:
    IBootloader(){}
    virtual ~IBootloader(){}

    /*!
     * @details
     *   Runs the bootloading process.
     */
    virtual void run() = 0;

    /*!
     * @details
     *   Gets the service locator, which should contains base objects after
     *   bootloading.
     */
    virtual IServiceLocator *serviceLocator() const = 0;

private:
    Q_DISABLE_COPY(IBootloader)
};

#endif // IBOOTLOADER_H
