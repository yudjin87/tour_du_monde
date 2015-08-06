/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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
#include <carto/carto_api.h>
#include <carousel/commands/BaseUndoableCommand.h>

class ITourDuMondeDocumentController;
class ILegendClass;

class CARTO_API ChangeLegendClassCommand : public BaseUndoableCommand
{
    Q_OBJECT
public:
    ChangeLegendClassCommand(IUndoStack *stack, ITourDuMondeDocumentController *docContr, QObject* parent = nullptr);

    void setLegendClass(ILegendClass* legendClass);

    void setDescription(const QString& description);
    void setLabel(const QString& label);
    void setVisible(const bool isVisible);

    void redo() override;
    void undo() override;

private:
    ITourDuMondeDocumentController *m_docContr;
    ILegendClass* m_legendClass;
    QString m_newDescription;
    QString m_newLabel;
    bool m_newVisibility;
    QString m_oldDescription;
    QString m_oldLabel;
    bool m_oldVisibility;
};
