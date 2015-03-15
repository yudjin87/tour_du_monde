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

#include "ComponentsDialogTest.h"
#include "fakes/FakeEnableComponentCommand.h"

#include <carousel/componentsystem/ComponentDefinition.h>
#include <carousel/componentsystem/ComponentDependencies.h>
#include <carousel/componentsystem/ProxyComponent.h>
#include <components/componentsystemui/ComponentDefinitionsModel.h>
#include <components/componentsystemui/ComponentsDialog.h>

#include <carousel/utils/ServiceLocator.h>

#include <QtWidgets/QUndoStack>

namespace {

ComponentDefinition *createDefinition(QString name, bool builtIn, QString compLocation, QString defLocation, QString description, QString product, QString shortName)
{
    ComponentDefinition *def = new ComponentDefinition(name, builtIn);
    //def->setAvailability(availability);
    if (!builtIn) {
        def->setComponentLocation(compLocation);
        def->setDefinitionLocation(defLocation);
        def->setVersion(1, 2, 3, 4);
    }
    def->setDescription(description);
    def->setProductName(product);
    def->setShortComponentName(shortName);

    def->setError(QString("Cannot parse file %1").arg(defLocation));

    return def;
}

}

ComponentsDialogTest::ComponentsDialogTest(QObject *parent)
    : QObject(parent)
    , locator(new ServiceLocator())
{

    dependencies = new ComponentDependencies(this);
    for (int i = 0; i < 13; ++i) {
        IComponent *comp = new ProxyComponent(createDefinition(QString("org.tests.Component%1").arg(i), (i % 3), "/to/nowhere/library", "/to/nowhere/definition", "Description", "ComponentA product", QString("Component %1").arg(i)));
        comp->setState(IComponent::State( i % 8));
        components.push_back(comp);
        dependencies->addComponent(comp);
    }

    // -- used for the dialog --
    locator->registerInstance(new QUndoStack(this));
    auto creator = [this](){return new FakeEnableComponentCommand(dependencies);};
    locator->registerType<EnableComponentCommand>(creator);

    //--------------------------

    model = new ComponentDefinitionsModel(dependencies->components());
    model->injectServiceLocator(locator);
    dialog = new ComponentsDialog(model);
}

ComponentsDialogTest::~ComponentsDialogTest()
{
    delete model;
    delete dialog;
    delete locator;
}

void ComponentsDialogTest::test()
{
    dialog->show();
}

