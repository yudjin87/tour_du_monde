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

#ifndef TESTCOMPONENTDEFINITION_H
#define TESTCOMPONENTDEFINITION_H

#include <componentsystem/IComponentDefinition.h>

class TestComponentDefinition : public IComponentDefinition
{
    Q_OBJECT
public:
    TestComponentDefinition();
    const QString &productName() const;
    const QString &description() const;
    Availability availability() const;
    void setAvailability(Availability i_new_mode);
    IComponent *component() const;
    const QStringList &parents() const;
    const QString &componentName() const {throw "Not implemented";}
    const QString &componentLocation() const {throw "Not implemented";}
    void loadAvailability() {throw "Not implemented";}

public:
    bool m_setAvailabilityCalled;
    QStringList m_dependencies;

private:
    Availability m_availability;
    QString m_productName;
    QString m_description;
};

#endif // TESTCOMPONENTDEFINITION_H
