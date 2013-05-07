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

#ifndef MOCKINTERACTIONSERVICE_H
#define MOCKINTERACTIONSERVICE_H

#include <interactivity/IInteractionService.h>

class MockInteractionService : public IInteractionService
{
public:
    MockInteractionService();

    ITool *activeTool();
    ICatalogs &catalogs();
    const ICatalogs &catalogs() const;
    IInputInterceptor *inputInterceptor();
    QMainWindow &mainWindow();
    void resetUi();
    void setActiveTool(ITool *activeTool);
    void setConfigurationDelegate(IComponentConfigurationDelegate *configurationDelegate);
    void setInputInterceptor(IInputInterceptor *inputInterceptor);
    void saveUiState(int version = 0);
    void loadUiState(int version = 0);

public:
    ITool *m_activeTool;
};

#endif // MOCKINTERACTIONSERVICE_H
