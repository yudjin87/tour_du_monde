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

#include <carto/commands/ChangeLegendClassCommand.h>
#include <carto/IMap.h>
#include <carto/ILegendClass.h>
#include <carto/ITourDuMondeDocument.h>
#include <carto/ITourDuMondeDocumentController.h>

ChangeLegendClassCommand::ChangeLegendClassCommand(IUndoStack *stack, ITourDuMondeDocumentController *docContr, QObject *parent)
    : BaseUndoableCommand(stack, parent)
    , m_docContr(docContr)
    , m_legendClass(nullptr)
    , m_newDescription()
    , m_newLabel()
    , m_newVisibility(false)
    , m_oldDescription()
    , m_oldLabel()
    , m_oldVisibility(false)
{
    setText("Legend class style changing");
}

void ChangeLegendClassCommand::setLegendClass(ILegendClass *legendClass)
{
    m_legendClass = legendClass;
}

void ChangeLegendClassCommand::setDescription(const QString &description)
{
    m_newDescription = description;
}

void ChangeLegendClassCommand::setLabel(const QString &label)
{
    m_newLabel = label;
}

void ChangeLegendClassCommand::setVisible(const bool isVisible)
{
    m_newVisibility = isVisible;
}

void ChangeLegendClassCommand::redo()
{
    m_oldDescription = m_legendClass->description();
    m_oldLabel = m_legendClass->label();
    m_oldVisibility = m_legendClass->isVisible();

    m_legendClass->setDescription(m_newDescription);
    m_legendClass->setLabel(m_newLabel);
    m_legendClass->setVisible(m_newVisibility);

    ITourDuMondeDocument *doc = m_docContr->document();
    IMap* map = doc->map();
    map->refresh();
}

void ChangeLegendClassCommand::undo()
{
    m_legendClass->setDescription(m_oldDescription);
    m_legendClass->setLabel(m_oldLabel);
    m_legendClass->setVisible(m_oldVisibility);

    ITourDuMondeDocument *doc = m_docContr->document();
    IMap* map = doc->map();
    map->refresh();
}
