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
#include <geodatabase/geodatabase_api.h>

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QObject>

#include <memory>

class IDataset;

// strange hack... Memory management should be reviewed
template <typename TPointer>
class OwnedList: public QList<TPointer> // omg, todo!! so old and weir code
{
    ~OwnedList()
    {
        for(int i = 0; i < this->size(); ++i)
            delete this->at(i);
    }
};

// Workspace in the geodatabase data model corresponds to a geodatabase,
// an ArcInfo coverage workspace, or a folder with shapefiles.
// A workspace is a container of spatial and non-spatial datasets such as feature classes,
// raster datasets, and tables. It provides methods to instantiate existing datasets and to create new datasets.

// Workspaces are classified into types specified by the WorkspaceType enumeration: FileSystemWorkspace, LocalDatabaseWorkspace, and RemoteDatabaseWorkspace.
class GEODATABASE_API IWorkspace : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString pathName READ pathName)
public:
    enum esriDatasetType {
        FeatureClassDT = 5,
        RasterCatalogDT = 16
    };

    IWorkspace(){}

    virtual QString pathName() const = 0;

public slots:
    virtual OwnedList<IDataset *> *datasets(esriDatasetType byType) = 0;

private:
    Q_DISABLE_COPY(IWorkspace)
};

typedef std::shared_ptr<IWorkspace> IWorkspaceSPtr;

