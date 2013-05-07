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

#include "MockInteractionService.h"

//------------------------------------------------------------------------------
MockInteractionService::MockInteractionService()
    : m_activeTool(nullptr)
{
}

//------------------------------------------------------------------------------
ITool *MockInteractionService::activeTool()
{
    throw "Not Implemented.";
}

//------------------------------------------------------------------------------
ICatalogs &MockInteractionService::catalogs()
{
    throw "Not Implemented.";
}

//------------------------------------------------------------------------------
const ICatalogs &MockInteractionService::catalogs() const
{
    throw "Not Implemented.";
}

//------------------------------------------------------------------------------
IInputInterceptor *MockInteractionService::inputInterceptor()
{
    throw "Not Implemented.";
}

//------------------------------------------------------------------------------
QMainWindow &MockInteractionService::mainWindow()
{
    throw "Not Implemented.";
}

//------------------------------------------------------------------------------
void MockInteractionService::setActiveTool(ITool * activeTool)
{
    m_activeTool = activeTool;
}

//------------------------------------------------------------------------------
void MockInteractionService::setConfigurationDelegate(IComponentConfigurationDelegate * /*configurationDelegate*/)
{
    throw "Not Implemented.";
}

//------------------------------------------------------------------------------
void MockInteractionService::setInputInterceptor(IInputInterceptor * /*inputInterceptor*/)
{
    throw "Not Implemented.";
}

//------------------------------------------------------------------------------
void MockInteractionService::saveUiState(int /*version*/)
{
    throw "Not Implemented.";
}

//------------------------------------------------------------------------------
void MockInteractionService::loadUiState(int /*version*/)
{
    throw "Not Implemented.";
}

//------------------------------------------------------------------------------
void MockInteractionService::resetUi()
{
    throw "Not Implemented.";
}

//------------------------------------------------------------------------------
