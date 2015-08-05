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

#include "carto/TourDeMondeDocumentController.h"
#include "carto/TourDeMondeDocument.h"
#include "carto/Map.h"

TourDeMondeDocumentController::TourDeMondeDocumentController(IDisplay *display)
    : m_document(new TourDeMondeDocument())
{
    m_document->addMap(new Map(m_document.get(), display));
    connect(m_document.get(), &ITourDeMondeDocument::nameChanged, this, &ITourDeMondeDocumentController::activeDocumentNameChanged);
}

TourDeMondeDocumentController::~TourDeMondeDocumentController()
{
}

ITourDeMondeDocument *TourDeMondeDocumentController::document()
{
    return m_document.get();
}

void TourDeMondeDocumentController::setDocument(ITourDeMondeDocument *doc)
{
    m_document.reset(doc);
    if (m_document)
    {
        connect(m_document.get(), &ITourDeMondeDocument::nameChanged, this, &ITourDeMondeDocumentController::activeDocumentNameChanged);
    }

    emit activeDocumentChanged(m_document.get());
    emit activeDocumentNameChanged(activeDocumentName());
}

QString TourDeMondeDocumentController::activeDocumentName() const
{
    return m_document == nullptr ? "Empty" : m_document->name();
}

