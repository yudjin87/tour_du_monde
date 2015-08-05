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

#include <geodatabase/IFeatureClassLoader.h>
#include <geodatabase/ShapeType.h>

#include <QtCore/QFileInfo>

#include <memory>

class BinaryReader;

class FeatureClassLoader : public IFeatureClassLoader
{
public:
    FeatureClassLoader(const QString &dirPath);
    ~FeatureClassLoader();

    LoadResult open(const QString &name) override;

    bool hasNext() override;
    void goToFirst() override;

    Geometry::Type geometryType() const override;
    QRectF boundingBox() const override;

    void loadFeature(IFeature* feature) override;

    QFileInfo source() const;

private:
    LoadResult readHeader(const int64_t fileSize);

private:
    const QString m_dirPath;
    QFileInfo m_file;
    std::unique_ptr<BinaryReader> m_reader;
    ShapeType m_shapeType;
    QRectF m_boundingBox;
};
