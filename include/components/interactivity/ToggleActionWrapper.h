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

#ifndef TOGGLEACTIONWRAPPER_H
#define TOGGLEACTIONWRAPPER_H

#include <components/interactivity/Operation.h>

/*!
 * @brief
 *   This class is a wrapper for the toggle actions.
 * @details
 *   Since carousel interactivity component uses IOperationCatalog for storing
 *   operations, already existed QActions (like QDockWidget::toggleViewAction())
 *   should be wrapped into the Operation.
 *
 *   This class provides synchronization mechanizm for between a toggle action and
 *   current Operation. To wrap action just create new instance of the ToggleActionWrapper
 *   with specified customization, like text or icon:
 * @code
 *   void MyInteractiveExtension::configureGui(ICatalogs &inCatalogs, IServiceLocator *serviceLocator)
 *   {
 *       IDockWidgetCatalog &catalog = inCatalogs.dockWidgetCatalog();
 *       QListView *view = new QListView();
 *       QStringListModel *model = getMyModel(serviceLocator);
 *       view->setModel(model);
 *       QDockWidget *layersDock = catalog.addDockWidget(view, "Layers tree");
 *
 *       Operation *toogleTree = new ToggleActionWrapper(layersDock->toggleViewAction(), QIcon(":/layerTree.png"));
 *       inCatalogs.operationCatalog().add(toogleTree);
 *
 *       QMenu *viewMenu = inCatalogs.menuCatalog().addMenu("View");
 *       viewMenu->addAction(toogleTree);
 *   }
 * @endcode
 */
class INTERACTIVITY_API ToggleActionWrapper : public Operation
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{ToggleActionWrapper} using @a toogleAction action for wrapping.
     */
    ToggleActionWrapper(QAction *toogleAction);

    /*!
     * @details
     * @overload
     */
    ToggleActionWrapper(QAction *toogleAction, const QString &text);

    /*!
     * @details
     * @overload
     */
    ToggleActionWrapper(QAction *toogleAction, const QIcon &icon);

    /*!
     * @details
     * @overload
     */
    ToggleActionWrapper(QAction *toogleAction, const QIcon &icon, const QString &text);

    /*!
     * @details
     *    Triggers wrapped action.
     */
    void execute();

    /*!
     * @details
     *    Triggers wrapped action.
     */
    void stopExecuting();

private slots:
    void onActionChanged(bool checked);

private:
    QAction *m_action;
};

#endif // TOGGLEACTIONWRAPPER_H
