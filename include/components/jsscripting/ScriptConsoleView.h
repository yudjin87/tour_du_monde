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

#ifndef SCRIPTCONSOLEVIEW_H
#define SCRIPTCONSOLE_H

#include <components/jsscripting/jsscripting_global.h>

#include <QtWidgets/QWidget>

namespace Ui
{
class ScriptConsoleView;
}

class JSSCRIPTING_API ScriptConsoleView : public QWidget
{
    Q_OBJECT    
public:
    explicit ScriptConsoleView(QWidget *parent = nullptr);
    ~ScriptConsoleView();
    
private:
    Ui::ScriptConsoleView *ui;
};

#endif // SCRIPTCONSOLEVIEW_H
