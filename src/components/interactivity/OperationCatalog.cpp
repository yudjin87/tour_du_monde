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

#include "OperationCatalog.h"

#include "Operation.h"

#include <QtCore/QtAlgorithms>
//------------------------------------------------------------------------------
OperationCatalog::OperationCatalog()
    : m_serviceLocator(nullptr)
{
}

//------------------------------------------------------------------------------
OperationCatalog::~OperationCatalog()
{
    qDeleteAll(m_operations);
}

//------------------------------------------------------------------------------
Operation *OperationCatalog::add(Operation *newOperation)
{
    m_operations.push_back(newOperation);
    newOperation->initialize(m_serviceLocator);

    onOperationAdded(newOperation);

    return newOperation;
}

//------------------------------------------------------------------------------
QList<Operation *> OperationCatalog::operations() const
{
    return m_operations;
}

//------------------------------------------------------------------------------
QList<Operation *> OperationCatalog::operations(const QString &byCategory) const
{
    QList<Operation *> operations;
    for (Operation *operation : m_operations)
        if (operation->category() == byCategory)
            operations.push_back(operation);

    return operations;
}

//------------------------------------------------------------------------------
void OperationCatalog::deleteOperation(const QString &name)
{
    Operation *operation = find(name);
    deleteOperation(operation);
}

//------------------------------------------------------------------------------
void OperationCatalog::deleteOperation(Operation *operation)
{
    if(m_operations.removeOne(operation))
        delete operation;
}

//------------------------------------------------------------------------------
Operation *OperationCatalog::find(const QString &name)
{
    return const_cast<Operation *>(static_cast<const OperationCatalog &>(*this).find(name));
}

//------------------------------------------------------------------------------
const Operation *OperationCatalog::find(const QString &name) const
{
    for (Operation *operation : m_operations)
        if (operation->name() == name)
            return operation;

    return nullptr;
}

//------------------------------------------------------------------------------
void OperationCatalog::setStartupData(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
}

//------------------------------------------------------------------------------
void OperationCatalog::onOperationAdded(Operation *operation)
{
    emit operationAdded(operation);
}

//------------------------------------------------------------------------------

