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

#ifndef OPERATION_H
#define OPERATION_H

#include "interactivity_global.h"

#include "IOperation.h"

#include <QtWidgets/QAction>

/*!
 * @brief
 *   Inherit this abstract class to create a operations provides user to interact
 *   with application.
 * @details
 *   One of the way of user interaction with Carousel based applications are the operations,
 *   which call application essentials.
 *   You can create the following types of operations:
 *   @li @a Buttons and @a menu @a items are the simplest types of operations.
 *   Buttons generally appear as icons on toolbars and menu items appear in menus. A simple
 *   action is performed when the button or menu item is clicked.
 *   @li @a Tools are similar to buttons but they also require interaction with the application's
 *   display. The "Zoom In" operation is a good example of a tool - you click or drag a rectangle
 *   over a widget before the display is redrawn to show the widget contents in more detail.
 *
 *   When you are creating a new operation, you must derived from the this class in your
 *   class code. This class determines the behavior and properties of simple operations
 *   such as buttons and menu items. For example, it declares operation properties
 *   such as name, category, icon, desctiptive text that used in QAction subclass - Operation
 *   and in the Customization dialog.
 *   It also defines what action happens when the operation is clicked.
 *
 *   You should implement at least execute() method in the derived class.
 */
class INTERACTIVITY_API Operation : public QAction, virtual public IOperation
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{Operation} with action group, if any.
     *   If the action group not null, this operation
     *   will be automatically inserted into the group.
     */
    Operation(QActionGroup *actionGroup = nullptr);

    /*!
     * @details
     * @constructor{Operation} with action group, if any.
     *   If the action group not null, this operation
     *   will be automatically inserted into the group.
     *
     *   The Operation uses a stripped version of @a text (e.g. "&Menu Option..." becomes
     *   "Menu Option") as descriptive text for tool buttons. You can override
     *   this by setting a specific description with setText(). The same text will be
     *   used for tooltips unless you specify a different text using setToolTip().
     */
    Operation(const QString &text, QActionGroup *actionGroup = nullptr);

    /*!
     * @details
     * @constructor{Operation} with action group, if any.
     *   If the action group not null, this operation
     *   will be automatically inserted into the group.
     *
     *   The Operation uses a stripped version of @a text (e.g. "&Menu Option..." becomes
     *   "Menu Option") as descriptive text for tool buttons. You can override
     *   this by setting a specific description with setText(). The same text will be
     *   used for tooltips unless you specify a different text using setToolTip().
     */
    Operation(const QIcon &icon, const QString &text, QActionGroup *actionGroup = nullptr);
    ~Operation();

    /*!
     * @details
     *   The name of the category with which this operation is associated.
     *   It determines where the operation will appear in the Operations panel
     *   of the Customize dialog.
     */
    QString category() const override;

    /*!
     * @details
     *   If operation is checkable, this method called after user switch off
     *   this operation.
     *
     *   It is also emmits executingStopped() signal.
     */
    void stopExecuting() override;

    /*!
     * @details
     *   Called by carousel interactivity system to gives the operation a hook into
     *   the application.
     *   When subclassing Operation, use the initialize() method to get a hook to the
     *   application. When the final, complete boot loading takes place, the initialize()
     *   method gets called for every registered operation.
     *
     *   Does nothing by default.
     */
    void initialize(IServiceLocator *serviceLocator) override;

    /*!
     * @details
     *   This property of a operation is a programmatic identifying name string.
     *   By convention, a operation's name should include its category name. The format of
     *   the @a name string should be <category>.<text>. Since it is an identifier of the
     *   operation, this property should not be localized.
     *   This property used to store user's customization.
     *   @note the text() property of a operation is the string that appears when the operation
     *   is placed on a operation bar.
     */
    QString name() const override;

signals:
    /*!
     * @details
     *   This signal is emited when operation is deactivated.
     */
    void executingStopped() override;

protected:
    /*!
     * @details
     *   Sets the name of the category with which this operation is associated.
     *   It determines where the operation will appear in the Operations panel
     *   of the Customize dialog.
     */
    void setCategory(const QString &category);

    /*!
     * @details
     *   Sets the programmatic identifying name string.
     *   By convention, a operation's name should include its category name. The format of
     *   the @a name string should be <category>.<text>. Since it is an identifier of the
     *   operation, this property should not be localized.
     *   This property used to store user's customization.
     *   @note the text() property of a operation is the string that appears when the operation
     *   is placed on a operation bar.
     */
    void setName(const QString &name);

    /*!
     * @details
     *   To provide convinient execute() and stopExecuting() methods Operation class subscribes
     *   to the base QAction class' signals QAction::toggled() and QAction::triggered(). It is already
     *   done in the constructor, but it may required to connect explicitly, e.g. after disconnecting.
     * @sa disconectFromSignals
     */
    void connectToSignals();

    /*!
     * @details
     *   To provide convinient execute() and stopExecuting() methods Operation class subscribes
     *   to the base QAction class' signals QAction::toggled() and QAction::triggered(). But
     *   for some cases may required to change, for example, checked() property silencely, without
     *   invoking execute() or stopExecuting(). To do it you should call disconectFromSignals() first
     *   and then connectToSignals againg.
     * @sa connectToSignals
     */
    void disconectFromSignals();

private slots:
    void onTriggered(bool checked);
    void onToggled(bool checked);

private:
    QString m_category;
    QString m_name;
    QMetaObject::Connection m_triggeredConnection;
    QMetaObject::Connection m_toggledConnection;
};

#endif // OPERATION_H
