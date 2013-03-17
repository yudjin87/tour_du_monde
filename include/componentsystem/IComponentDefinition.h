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

#ifndef ICOMPONENTDEFINITION_H
#define ICOMPONENTDEFINITION_H

#include "componentsystem/componentsystem_global.h"
#include "componentsystem/IComponentExtension.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>

class IComponent;

/*!
 * @brief
 *   The abstract IComponentDefinition class describes the component meta information.
 * @details
 *   This class is used in the Components dialog to provide to user information about
 *   the component. It also allow for user to enable or disable your component.
 *
 *   This class also specified that the current component has dependencies
 *   on another ones - on its 'parents'.
 *
 *   You should return names of the parent components in the parents() method
 *   if your component uses some services from another one - it is guaranteed
 *   that your component will be started up after all dependent components will.
 */
class COMP_API IComponentDefinition : public QObject
{
    Q_OBJECT
    Q_ENUMS(Availability)

    /*!
     * @details
     *   Gets or sets the value specified whether this component is enabled, disabled, or unavailable.
     *   When the availability is enabled, the component is checked in the Components dialog.
     */
    Q_PROPERTY(Availability availability READ availability WRITE setAvailability NOTIFY availabilityChanged)
public:

    /*!
     * @details
     *   Component availability states.
     */
    enum Availability
    {
        /*!
         * @details
         *   Enabled for use.
         */
        Enabled,

        /*!
         * @details
         *   Disabled by the user. If component is disabled, child
         *   components that have dependency from this component,
         *   cannot be started.
         */
        Disabled,

        /*!
         * @details
         *   Unavailable - not licensed. If component is unavailable, child
         *   components that have dependency from this component,
         *   cannot be started.
         */
        Unavailable
    };

    IComponentDefinition(){}

public slots:

    virtual void addParent(const QString &parent) = 0;

    /*!
     * @details
     *   Gets the value specified whether this component is enabled, disabled, or unavailable.
     *   When the availability is enabled, the component is checked in the Components dialog.
     * @sa setAvailability
     */
    virtual Availability availability() const = 0;

    /*!
     * @details
     *   Returns the defined component.
     */
    virtual IComponent *component() const = 0;

    /*!
     * @details
     *   Returns the component location (for loaded components). It might be absolute or
     *   relative path.
     *
     *   Returns empty string for explicitly loaded components (static components).
     */
    virtual const QString &componentLocation() const = 0;

    /*!
     * @details
     *   Returns the component name. It is a shortcut for the component()->name().
     */
    virtual const QString &componentName() const = 0;

    /*!
     * @details
     *   Gets the detailed description text that is displayed for this component in the
     *   About this component box in the Components dialog.
     */
    virtual const QString &description() const = 0;

    /*!
     * @details
     *   Loads component availability using component name.
     */
    virtual void loadAvailability() = 0;

    /*!
     * @details
     *   Gets the list of parent (dependent) components names.
     */
    virtual const QStringList &parents() const = 0;

    /*!
     * @details
     *   Gets the the name that is displayed for this component in the Components dialog.
     */
    virtual const QString &productName() const = 0;

    /*!
     * @details
     *   Sets the value specified whether this component is enabled or disabled.
     *   The checked state of the component is saved in the user settings.
     * @sa availability
     */
    virtual void setAvailability(Availability i_newMode) = 0;

    /*!
     * @details
     *   Sets the component description.
     */
    virtual void setDescription(const QString &description) = 0;

    /*!
     * @details
     *   Sets the product name.
     */
    virtual void setProductName(const QString &productName) = 0;

    /*!
     * @details
     *   Sets the component location.
     */
    virtual void setComponentLocation(const QString &componentLocation) = 0;

signals:
    /*!
     * @details
     *   This signal is emited when extension's availability changed.
     * @sa setAvailability
     */
    void availabilityChanged(Availability);

private:
    Q_DISABLE_COPY(IComponentDefinition)
};


#endif // ICOMPONENTDEFINITION_H
