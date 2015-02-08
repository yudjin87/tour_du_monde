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

#include "ToolBase.h"

#include "IInteractionService.h"

#include <carousel/utils/IServiceLocator.h>

#include <assert.h>
//------------------------------------------------------------------------------
ToolBase::ToolBase(QActionGroup *actionGroup)
    : Operation(actionGroup)
    , m_serviceLocator(nullptr)
    , m_interactionService(nullptr)
{
    setCheckable(true);
}

//------------------------------------------------------------------------------
ToolBase::ToolBase(const QString &text, QActionGroup *actionGroup)
    : Operation(text, actionGroup)
    , m_serviceLocator(nullptr)
    , m_interactionService(nullptr)
{
    setCheckable(true);
}

//------------------------------------------------------------------------------
ToolBase::ToolBase(const QIcon &icon, const QString &text, QActionGroup *actionGroup)
    : Operation(icon, text, actionGroup)
    , m_serviceLocator(nullptr)
    , m_interactionService(nullptr)
{
    setCheckable(true);
}

//------------------------------------------------------------------------------
ToolBase::~ToolBase()
{
    m_serviceLocator = nullptr;
    m_interactionService = nullptr;
}

//------------------------------------------------------------------------------
void ToolBase::execute()
{
    m_interactionService->setActiveTool(this);
    setChecked(true);
}

//------------------------------------------------------------------------------
void ToolBase::stopExecuting()
{
    Operation::stopExecuting();
    setChecked(false);
}

//------------------------------------------------------------------------------
void ToolBase::initialize(IServiceLocator *serviceLocator)
{
    m_serviceLocator = serviceLocator;
    assert(serviceLocator != nullptr);

    m_interactionService = m_serviceLocator->locate<IInteractionService>();
    assert(m_interactionService != nullptr);
}

//------------------------------------------------------------------------------
bool ToolBase::onContextMenu(QContextMenuEvent *event)
{
    Q_UNUSED(event)
    return false;
}

//------------------------------------------------------------------------------
bool ToolBase::onDoubleClick(QMouseEvent *event)
{
    Q_UNUSED(event)
    return false;
}

//------------------------------------------------------------------------------
bool ToolBase::onKeyDown(QKeyEvent *event)
{
    Q_UNUSED(event)
    return false;
}

//------------------------------------------------------------------------------
bool ToolBase::onKeyUp(QKeyEvent *event)
{
    Q_UNUSED(event)
    return false;
}

//------------------------------------------------------------------------------
bool ToolBase::onMouseDown(QMouseEvent *event)
{
    Q_UNUSED(event)
    return false;
}

//------------------------------------------------------------------------------
bool ToolBase::onMouseMove(QMouseEvent *event)
{
    Q_UNUSED(event)
    return false;
}

//------------------------------------------------------------------------------
bool ToolBase::onMouseUp(QMouseEvent *event)
{
    Q_UNUSED(event)
    return false;
}

//------------------------------------------------------------------------------
