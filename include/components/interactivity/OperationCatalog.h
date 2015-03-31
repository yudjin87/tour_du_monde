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

#pragma once
#include "interactivity_global.h"

#include "IOperationCatalog.h"

class IServiceLocator;

/*!
 * @brief
 *   Use OperationCatalog class to adding and fetching application operations.
 * @details
 *   This class allows you to add new operation that will be used
 *   in Custimozation dialog. Although you can add new operations/actions in the
 *   menus or toolbars directly, it is recomended to register all your operations
 *   in the catalog first - it's allow user to customize interface by adding
 *   your operations to the user defined toolbars.
 *
 *   Use IInteractionService::catalogs().operationCatalog() to get a reference to the operation collection
 *   to add operations specific to your extensions.
 */
class INTERACTIVITY_API OperationCatalog : public IOperationCatalog
{
    Q_OBJECT
public:
    OperationCatalog();
    ~OperationCatalog();

    /*!
     * @details
     *   Adds new operation to the catalog and initializes it
     *   with start up data. It takes ownership of the
     *   operation.
     *
     *   This method returns specified operation for the convenience.
     *   You can use returned value in the such way:
     * @code
     *   QMenu *fileMenu = menuCatalog.findMenuEverywhere(tr("File"));
     *   fileMenu->addAction(operationCatalog->add(new MyPrintOperation()));
     * @endcode
     */
    Operation *add(Operation *newOperation) override;

    /*!
     * @details
     *   Returns all operations, added to the catalog.
     */
    QList<Operation *> operations() const override;

    /*!
     * @details
     *   Returns all operations with specified category.
     */
    QList<Operation *> operations(const QString &byCategory) const override;

    /*!
     * @details
     *   Searches for the operation specified by @a name, removes if any
     *   from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     */
    void deleteOperation(const QString &name) override;

    /*!
     * @details
     *   Removes specified operation from containter and calls delete.
     *
     *   Usualy you should not use this method directly - it is used
     *   only by IComponentConfigurationDelegate to deconfigure component
     *   and revert changes is did.
     */
    void deleteOperation(Operation *operation) override;

    /*!
     * @details
     *   Searches for the operation specified by @a name. Note, that
     *   found name shold not be localized.
     *   @sa Operation::name()
     * @return
     *   Found operation. Null, if there are no operations with such name.
     */
    Operation *find(const QString &name) override;

    /*!
     * @details
     *   Searches for the operation specified by @a name. Note, that
     *   found name shold not be localized.
     *   @sa Operation::name()
     * @return
     *   Found operation. Null, if there are no operations with such name.
     */
    const Operation *find(const QString &name) const override;

    /*!
     * @details
     *   Sets the reference to the service locator wich operations
     *   will be initialized with.
     */
    void setStartupData(IServiceLocator *serviceLocator);

protected:
    /*!
     * @details
     *   Emits a operationAdded() signal when specified one is added to
     *   catalog.
     */
    virtual void onOperationAdded(Operation *operation);

private:
    QList<Operation *> m_operations;
    IServiceLocator *m_serviceLocator;
};

