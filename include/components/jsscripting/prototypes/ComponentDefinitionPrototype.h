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

#pragma once
#include <carousel/componentsystem/ComponentDefinition.h>

#include <QtCore/QObject>
#include <QtScript/QScriptable>

/*!
 * @brief
 */
class ComponentDefinitionPrototype : public QObject, public QScriptable
{
    Q_OBJECT
    Q_PROPERTY(IComponent *component READ component)
    Q_PROPERTY(const Version *version READ version)
    Q_PROPERTY(bool isBuiltIn READ isBuiltIn)
    Q_PROPERTY(QString componentLocation READ componentLocation)
    Q_PROPERTY(QString shortComponentName READ shortComponentName)
    Q_PROPERTY(QString componentName READ componentName)
    Q_PROPERTY(QString definitionLocation READ definitionLocation)
    Q_PROPERTY(QString description READ description)
    Q_PROPERTY(QString productName READ productName)
    Q_PROPERTY(QString provider READ provider)
    Q_PROPERTY(QString error READ error)
public:
    /*!
     * @details
     * @constructor{ComponentDefinitionPrototype}.
     */
    ComponentDefinitionPrototype(QObject *parent = nullptr);

    IComponent *component() const;
    const Version *version() const;
    bool isBuiltIn() const;
    const QString &componentLocation() const;
    const QString &shortComponentName() const;
    const QString &componentName() const;
    const QString &definitionLocation() const;
    const QString &description() const;
    const QString &productName() const;
    const QString &provider() const;
    const QString &error() const;

    // TODO: add to the property
    const ParentDefinitions &parents() const;


public slots:
    bool isCompatible(const IComponent *parent) const;
    bool isCompatible(const QString &name, const Version *version) const;
    bool isCompatible(const ParentDefinitions &parents) const;
    QString toString() const;

private:
    Q_DISABLE_COPY(ComponentDefinitionPrototype)
    ComponentDefinition *thisDef();
    const ComponentDefinition *thisDef() const;
};

Q_DECLARE_METATYPE(ComponentDefinition *)
Q_DECLARE_METATYPE(const ComponentDefinition *)

