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

class IScriptConsole;
class QSyntaxHighlighter;

class JSSCRIPTING_API ScriptConsoleView : public QWidget
{
    Q_OBJECT    
public:
    /*!
     * @details
     *   Takes ownership for hilighter.
     */
    ScriptConsoleView(IScriptConsole *console, QSyntaxHighlighter *hilighter, QWidget *parent = nullptr);
    ~ScriptConsoleView();
    
protected:
    bool eventFilter(QObject *sender, QEvent *event);

private slots:
    void onEnter();

private:
    void connectSignalsToSlots();
    void onPrevCommand();
    void onNextCommand();

private:
    Ui::ScriptConsoleView *m_ui;
    IScriptConsole *m_console;
    QSyntaxHighlighter *m_hilighter;
};

#endif // SCRIPTCONSOLEVIEW_H
