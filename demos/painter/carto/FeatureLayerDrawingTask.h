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

#ifndef FEATURELAYERDRAWINGTASK_H
#define FEATURELAYERDRAWINGTASK_H

#include <display/IDrawingTask.h>
#include <geodatabase/IFeatureClass.h>
#include <QtCore/QObject>

class FeatureRenderer;

class FeatureLayerDrawingTask : public QObject, public IDrawingTask
{
    Q_OBJECT
public:
    FeatureLayerDrawingTask(IFeatureClass::FeatureList &&features, FeatureRenderer* renderer, QObject* parent = nullptr);
    ~FeatureLayerDrawingTask();

    void draw(IDisplay &display) override;

private:
    const IFeatureClass::FeatureList m_features;
    FeatureRenderer* m_renderer;
};

#endif // FEATURELAYERDRAWINGTASK_H

