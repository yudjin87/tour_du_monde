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

#include "ComponentDefinitionsModel.h"
#include "EnableComponentCommand.h"
#include "InstallComponentsCommand.h"

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/IComponent.h>
#include <utils/ObservableList.h>
#include <utils/IServiceLocator.h>

#include <QtGui/QIcon>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QUndoStack>

//------------------------------------------------------------------------------
ComponentDefinitionsModel::ComponentDefinitionsModel(const ObservableList<IComponent *> &components, QObject *parent)
    : QAbstractTableModel(parent)
    , m_components(components)
    , m_locator(nullptr)
{
    m_components.installObserver(this);
}

//------------------------------------------------------------------------------
ComponentDefinitionsModel::~ComponentDefinitionsModel()
{
    m_components.removeObserver(this);
    m_locator = nullptr;
}

//------------------------------------------------------------------------------
void ComponentDefinitionsModel::injectServiceLocator(IServiceLocator *locator)
{
    m_locator = locator;
}

//------------------------------------------------------------------------------
Qt::ItemFlags ComponentDefinitionsModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (!index.isValid())
        return flags;

    const IComponent *comp = m_components.at(index.row());
    const ComponentDefinition *def = comp->definition();

    if (def->isBuiltIn())
        return Qt::NoItemFlags;
    else
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
}

//------------------------------------------------------------------------------
int ComponentDefinitionsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    if (parent.isValid())
        return 0;

    return m_components.size();
}

//------------------------------------------------------------------------------
int ComponentDefinitionsModel::columnCount(const QModelIndex &parent) const
{
    return (parent.column() > 0) ? 0 : 3;
}

//------------------------------------------------------------------------------
QVariant ComponentDefinitionsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QAbstractItemModel::headerData(section, orientation, role);

    switch (section) {
    case 0: return "Internal name";
    case 1: return "Name";
    case 2: return "Provider";
    default: return QVariant();
    }
}

//------------------------------------------------------------------------------
QVariant ComponentDefinitionsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.model() != this)
        return QVariant();

    const IComponent *comp = m_components.at(index.row());
    const ComponentDefinition *def = comp->definition();

    switch (role) {
    case Qt::EditRole:
    case Qt::DisplayRole:
        switch (index.column()) {
        case 0: return def->componentName();
        case 1: return def->productName();
        case 2: return def->provider();
        default:
            qWarning("data: invalid display value column %d", index.column());
            break;
        }
        break;

    case Qt::CheckStateRole:
        switch (index.column()) {
        case 0: return comp->availability() == IComponent::Enabled
                    ? Qt::Checked
                    : Qt::Unchecked;
        default: return QVariant::Invalid;
        }
        break;

    case Qt::ToolTipRole:
        if (index.column() == 0) {
            return def->isBuiltIn() ? tr("Built-in") : def->definitionLocation();
        } else {
            return QVariant::Invalid;
        }

    case Qt::TextColorRole:
        if (def->isBuiltIn())
            return QColor(QColor::fromRgb(128, 128, 128));
        else
            return QColor(QColor::fromRgb(0, 0, 0));

    case Qt::DecorationRole:
        if (index.column() == 0) {
            QIcon icon;
            return icon;
        }
        break;
    }

    return QVariant();
}

//------------------------------------------------------------------------------
bool ComponentDefinitionsModel::setData(const QModelIndex &index, const QVariant &, int role)
{
    if (!index.isValid()
            || index.column() != 0
            || (index.row() > m_components.size())
            || role != Qt::CheckStateRole)
        return false;

    onToogleEnable(index);

    // Reset availability state for all components
    emit dataChanged(createIndex(0, 0), createIndex(m_components.size(), 0));
    return true;
}

//------------------------------------------------------------------------------
void ComponentDefinitionsModel::onDescription(const QModelIndex &index)
{
    Q_UNUSED(index)
}

//------------------------------------------------------------------------------
void ComponentDefinitionsModel::onInstall()
{
    QFileDialog fileDialog(m_locator->locate<QMainWindow>(), "Install component");
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setNameFilter("Components (*.definition)"); // TODO: get from the app settings
    if (!fileDialog.exec())
        return;

    InstallComponentsCommand* command = m_locator->buildInstance<InstallComponentsCommand>();
    command->setSourceDirectoryPath(fileDialog.directory().absolutePath());

    foreach(const QString &fileName, fileDialog.selectedFiles())
        command->addDefinitionPath(fileName);

    QUndoStack *undo = m_locator->locate<QUndoStack>();
    undo->push(command);
}

//------------------------------------------------------------------------------
void ComponentDefinitionsModel::onToogleEnable(const QModelIndex &index)
{
    Q_ASSERT(m_locator != nullptr);

    EnableComponentCommand* command = m_locator->buildInstance<EnableComponentCommand>();
    IComponent *comp = m_components.at(index.row());
    command->addComponentToSwitchState(comp);

    QUndoStack *undo = m_locator->locate<QUndoStack>();
    undo->push(command);
}

//------------------------------------------------------------------------------
void ComponentDefinitionsModel::onChanged(const Changes<IComponent *> &changes)
{
    int addedItems = changes.affectedItems.size();
    int oldSize = m_components.size() - addedItems;
    beginInsertRows(QModelIndex(), oldSize, oldSize);
    endInsertRows();
}

//------------------------------------------------------------------------------
