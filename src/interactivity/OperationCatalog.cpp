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
    : mp_startupData(nullptr)
{
}

//------------------------------------------------------------------------------
OperationCatalog::~OperationCatalog()
{
    qDeleteAll(m_operations);
}

//------------------------------------------------------------------------------
Operation *OperationCatalog::add(Operation *ip_newOperation)
{
    m_operations.push_back(ip_newOperation);
    ip_newOperation->initialize(mp_startupData);

    onOperationAdded(ip_newOperation);

    return ip_newOperation;
}

//------------------------------------------------------------------------------
QList<Operation *> OperationCatalog::operations() const
{
    return m_operations;
}

//------------------------------------------------------------------------------
QList<Operation *> OperationCatalog::operations(const QString &i_byCategory) const
{
    QList<Operation *> operations;
    foreach(Operation *p_operation, m_operations)
        if (p_operation->category() == i_byCategory)
            operations.push_back(p_operation);

    return operations;
}

//------------------------------------------------------------------------------
void OperationCatalog::deleteOperation(const QString &i_name)
{
    Operation *operation = find(i_name);
    deleteOperation(operation);
}

//------------------------------------------------------------------------------
void OperationCatalog::deleteOperation(Operation *ip_operation)
{
    if(m_operations.removeOne(ip_operation))
        delete ip_operation;
}

//------------------------------------------------------------------------------
Operation *OperationCatalog::find(const QString &i_name)
{
    return const_cast<Operation *>(static_cast<const OperationCatalog &>(*this).find(i_name));
}

//------------------------------------------------------------------------------
const Operation *OperationCatalog::find(const QString &i_name) const
{
    foreach(Operation *p_operation, m_operations)
        if (p_operation->name() == i_name)
            return p_operation;

    return nullptr;
}

//------------------------------------------------------------------------------
void OperationCatalog::setStartupData(QObject *ip_startupData)
{
    mp_startupData = ip_startupData;
}

//------------------------------------------------------------------------------
void OperationCatalog::onOperationAdded(Operation *ip_operation)
{
    emit operationAdded(ip_operation);
}

//------------------------------------------------------------------------------

