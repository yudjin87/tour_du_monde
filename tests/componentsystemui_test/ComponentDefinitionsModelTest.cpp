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

#include "ComponentDefinitionsModelTest.h"

#include <componentsystem/ComponentDefinition.h>
#include <componentsystem/ComponentDependencies.h>
#include <componentsystem/ProxyComponent.h>
#include <componentsystemui/ComponentDefinitionsAdapter.h>
#include <componentsystemui/ComponentDefinitionsModel.h>

#include <QtCore/QtAlgorithms>
#include <QtCore/QTimer>
#include <QtGui/QSortFilterProxyModel>

//------------------------------------------------------------------------------
namespace {

ComponentDefinition *createDefinition(QString name,  bool builtIn, QString compLocation, QString defLocation, QString description, QString product)
{
    ComponentDefinition *def = new ComponentDefinition(name, builtIn);
    if (!builtIn) {
        def->setComponentLocation(compLocation);
        def->setDefinitionLocation(defLocation);
    }
    def->setDescription(description);
    def->setProductName(product);

    return def;
}

}

//------------------------------------------------------------------------------
ComponentDefinitionsModelTest::ComponentDefinitionsModelTest()
    : QTableView()
{
    dependencies = new ComponentDependencies(this);
    for (int i = 0; i < 11; ++i) {
        IComponent *comp = new ProxyComponent(createDefinition(QString("Component%1").arg(i), (i % 2), "/to/nowhere/library", "/to/nowhere/definition", "Description", "ComponentA product"));
        components.push_back(comp);
        dependencies->addComponent(comp);
    }

    ComponentDefinitionsAdapter *adapter = new ComponentDefinitionsAdapter(dependencies);
    ComponentDefinitionsModel *model = new ComponentDefinitionsModel(adapter, this);

    QSortFilterProxyModel *filterModel = new QSortFilterProxyModel(this);
    filterModel->setSourceModel(model);

    this->setModel(filterModel);
    this->setSortingEnabled(true);
    this->resizeColumnsToContents();
    this->setSelectionBehavior(QAbstractItemView::SelectRows);

    QTimer::singleShot(3000, this, SLOT(addNewOne()));
}

//------------------------------------------------------------------------------
ComponentDefinitionsModelTest::~ComponentDefinitionsModelTest()
{
    qDeleteAll(components);
}

//------------------------------------------------------------------------------
void ComponentDefinitionsModelTest::addNewOne()
{
    IComponent *comp = new ProxyComponent(createDefinition(QString("Component%1").arg(99), true, "/to/nowhere/library", "/to/nowhere/definition", "Description", "ComponentA product"));
    components.push_back(comp);
    dependencies->addComponent(comp);

    IComponent *comp2 = new ProxyComponent(createDefinition(QString("Component%1").arg(88), true, "/to/nowhere/library", "/to/nowhere/definition", "Description", "ComponentA product"));
    components.push_back(comp2);
    dependencies->addComponent(comp2);
}

//------------------------------------------------------------------------------
