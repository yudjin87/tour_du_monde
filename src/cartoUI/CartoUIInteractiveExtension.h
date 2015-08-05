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
#include <components/interactivity/IInteractiveExtension.h>

#include <QtCore/QObject>

class ITourDeMondeDocument;
class LayerTreeView;

class CartoUIInteractiveExtension : public QObject, public IInteractiveExtension
{
    Q_OBJECT
public:
    CartoUIInteractiveExtension(QObject *parent = nullptr);

    void configureGui(ICatalogs &inCatalogs, IServiceLocator *serviceLocator) override;

private:
    void onActiveDocumentChanged(ITourDeMondeDocument* document);

private:
    LayerTreeView *m_layersTree;
    IServiceLocator *m_serviceLocator;
};


