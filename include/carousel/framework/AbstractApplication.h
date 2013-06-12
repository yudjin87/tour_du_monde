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

#ifndef ABSTRACTAPPLICATION_H
#define ABSTRACTAPPLICATION_H

#include <carousel/framework/framework_global.h>

#include <QtWidgets/QApplication>

class IBootloader;
class IComponentManager;
class IServiceLocator;
class QMainWindow;

/*!
 * @brief
 *   The AbstractApplication object is the core object in the carousel and Qt applications.
 * @details
 *   This object represents the application itself that handles message loop (a QApplication).
 *   Instead of QApplication or QCoreApplication to start carousel AbstractApplication you
 *   should provide customized @a bootloader, that populates your application with components.
 *
 *   To start application call runApplicationLoop() method, that performs loading sequence and
 *   then starts exec() loop:
 *
 * @code
 *   #include "MyBootloader.h"
 *   #include <carousel/framework/AbstractApplication.h>
 *
 *   int main(int argc, char *argv[])
 *   {
 *       AbstractApplication application(argc, argv);
 *
 *       MyBootloader bootloader;
 *       return application.runApplicationLoop(bootloader);
 *   }
 * @endcode
 *
 *   During the loading sequence AbstractApplication runs a bootloader, connects to the
 *   QCoreApplication::aboutToQuit(), starts component manager and, finaly, shows a main window,
 *   which was created during the loading sequence.
 *   An AbstractApplication also stops component manager as a reaction on the
 *   QCoreApplication::aboutToQuit() signal.
 *
 *   You can create your own application class where you should setup application and organization
 *   name, or override default behaviour.
 */
class FRAMEWORK_API AbstractApplication : public QApplication
{
    Q_OBJECT
public:
    /*!
     * @constructor{AbstractApplication} using @a argc command line arguments in @a argv.
     */
    AbstractApplication(int &argc, char **argv, int flags = ApplicationFlags);
    ~AbstractApplication();

    /*!
     * @details
     *   Performs loading sequence using @a bootloader and then starts exec() loop.
     * @sa startLoadingSequence(), finishLoadingSequence()
     */
    virtual int runApplicationLoop(IBootloader &bootloader);

protected:
    /*!
     * @details
     *   Shuts down a component manager, obtained from the bootloader after the loading sequence.
     */
    virtual void shutdownComponentManager(IComponentManager *componentManager);

    /*!
     * @details
     *   Starts a component manager, obtained from the bootloader after the loading sequence.
     */
    virtual void startComponentManager(IComponentManager *componentManager);

    /*!
     * @details
     *   Starts a main window, obtained from the bootloader after the loading sequence.
     */
    virtual void showMainWindow(QMainWindow *mainWindow);

protected slots:
    /*!
     * @details
     *   Runs loading sequence using @a bootloader and connects to the
     *   QCoreApplication::aboutToQuit().
     */
    virtual void startLoadingSequence(IBootloader &bootloader);

    /*!
     * @details
     *   Finishes the loading sequence starting component manager and showing a main window.
     */
    virtual void finishLoadingSequence();

    /*!
     * @details
     *   Performs a finalazing actions such as shutting down a component manager.
     *   This slot is invoked on QCoreApplication::aboutToQuit() signal.
     */
    virtual void onAboutToQuit();

private:
    IServiceLocator *m_serviceLocator;
};

#endif // ABSTRACTAPPLICATION_H
