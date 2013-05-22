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

#include "framework/framework_global.h"

#include <QtGui/QApplication>

class IBootloader;
class IServiceLocator;
class QMainWindow;

class FRAMEWORK_API AbstractApplication : public QApplication
{
    Q_OBJECT
public:
    AbstractApplication();
    AbstractApplication(int &argc, char **argv, int flags = ApplicationFlags);
    AbstractApplication(int &argc, char **argv, bool GUIenabled, int flags = ApplicationFlags);
    AbstractApplication(int &argc, char **argv, Type type, int flags = ApplicationFlags);
    ~AbstractApplication();

    virtual int runApplicationLoop(IBootloader &bootloader);

protected slots:
    virtual void startLoadingSequence(IBootloader &bootloader);
    virtual void finishLoadingSequence();
    virtual void onAboutToQuit();

private:
    IServiceLocator *m_serviceLocator;
};

#endif // ABSTRACTAPPLICATION_H
