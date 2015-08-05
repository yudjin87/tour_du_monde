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

#include <QtCore/QObject>
#include <memory>

class IMap;

class CARTO_API ITourDeMondeDocument : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(IMap *map READ map)
public:
    virtual IMap *map() = 0;
    virtual const IMap *map() const = 0;
    virtual const QString &name() const = 0;
    virtual void setName(const QString &name) = 0;
    virtual void addMap(IMap *map) = 0;

signals:
    void nameChanged(QString name);

protected:
    ITourDeMondeDocument() = default;

private:
    Q_DISABLE_COPY(ITourDeMondeDocument)
};


typedef std::unique_ptr<ITourDeMondeDocument> ITourDeMondeDocumentUPtr;
