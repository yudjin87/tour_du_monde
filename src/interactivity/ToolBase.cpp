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

#include <framework/AbstractApplication.h>
#include <utils/IServiceLocator.h>

#include <assert.h>
//------------------------------------------------------------------------------
ToolBase::ToolBase(QActionGroup *ip_actionGroup)
    : Operation(ip_actionGroup)
    , mp_app(nullptr)
    , mp_interactionService(nullptr)
{
    setCheckable(true);
}

//------------------------------------------------------------------------------
ToolBase::ToolBase(const QString &i_text, QActionGroup *ip_actionGroup)
    : Operation(i_text, ip_actionGroup)
    , mp_app(nullptr)
    , mp_interactionService(nullptr)
{
    setCheckable(true);
}

//------------------------------------------------------------------------------
ToolBase::ToolBase(const QIcon &i_icon, const QString &i_text, QActionGroup *ip_actionGroup)
    : Operation(i_icon, i_text, ip_actionGroup)
    , mp_app(nullptr)
    , mp_interactionService(nullptr)
{
    setCheckable(true);
}

//------------------------------------------------------------------------------
ToolBase::~ToolBase()
{
    mp_app = nullptr;
    mp_interactionService = nullptr;
}

//------------------------------------------------------------------------------
void ToolBase::execute()
{
    mp_interactionService->setActiveTool(this);
}

//------------------------------------------------------------------------------
void ToolBase::stopExecuting()
{
    Operation::stopExecuting();
}

//------------------------------------------------------------------------------
void ToolBase::initialize(QObject *ip_startUpData)
{
    mp_app = dynamic_cast<AbstractApplication *>(ip_startUpData);
    assert(mp_app != nullptr);

    mp_interactionService = mp_app->serviceLocator().locate<IInteractionService>();
    assert(mp_interactionService != nullptr);
}

//------------------------------------------------------------------------------
bool ToolBase::onContextMenu(QContextMenuEvent * /*ip_event*/)
{
    return false;
}

//------------------------------------------------------------------------------
void ToolBase::onDoubleClick(QMouseEvent * /*ip_event*/)
{
}

//------------------------------------------------------------------------------
void ToolBase::onKeyDown(QKeyEvent * /*ip_event*/)
{
}

//------------------------------------------------------------------------------
void ToolBase::onKeyUp(QKeyEvent * /*ip_event*/)
{
}

//------------------------------------------------------------------------------
void ToolBase::onMouseDown(QMouseEvent * /*ip_event*/)
{
}

//------------------------------------------------------------------------------
void ToolBase::onMouseMove(QMouseEvent * /*ip_event*/)
{
}

//------------------------------------------------------------------------------
void ToolBase::onMouseUp(QMouseEvent * /*ip_event*/)
{
}

//------------------------------------------------------------------------------
