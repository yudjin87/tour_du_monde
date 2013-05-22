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
#ifndef CAROUSELBOOTLOADER_H
#define CAROUSELBOOTLOADER_H

#include "booting/BootloaderBase.h"

/*!
 * @brief
 *   It is a base class that provides a basic booting sequence that registers most of
 *   the carousel library assets in a IServiceLocator.
 * @details
 *   This class must be overridden to provide application specific boot loading sequence. See safeRun()
 *   method for the details.
 */
class BOOTING_API CarouselBootloader : public BootloaderBase
{
    Q_OBJECT
public:
    CarouselBootloader();
    ~CarouselBootloader();

protected:
    /*!
     * @details
     *   Add all components registered in provider to the component manager.
     */
    void configureComponentManager();

    /*!
     * @details
     *   Configure service locator adding the IComponentManager and IComponentProvider.
     *   May be overridden in a derived class to add specific services required by the application.
     */
    void configureServiceLocator();

    /*!
     * @details
     *   Initializes the component provider.
     */
    void initialiseComponentProvider();

    /*!
     * @details
     *   Performs the carousel-specific booting sequence:
     *   \li first calls BootloaderBase::createLoggerEngine() - override this method to instantiate logger facade over your favorite logging system;
     *   \li then calls BootloaderBase::createServiceLocator();
     *   \li then calls BootloaderBase::createComponentManager();
     *   \li then calls BootloaderBase::createComponentProvider() - override this method to instantiate specific component provider;
     *   \li then calls BootloaderBase::createMainWindow();
     *   \li then calls BootloaderBase::configureComponentProvider() - override this method to register components statically or specify parameters for their dynamic discovering;
     *   \li then calls configureServiceLocator();
     *   \li then calls initialiseComponentProvider();
     *   \li and finally calls configureComponentManager().
     */
    void safeRun();
};

#endif // CAROUSELBOOTLOADER_H
