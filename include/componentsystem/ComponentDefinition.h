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

#ifndef COMPONENTDEFINITION_H
#define COMPONENTDEFINITION_H

#include "componentsystem/IComponentDefinition.h"

/*!
 * @brief
 *   It is a default implementation of the IComponentDefinition interface.
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
class COMP_API ComponentDefinition : public IComponentDefinition
{
    Q_OBJECT
public:
    /*!
     * @details
     *   Initialises a new instance of the ComponentDefinition class.
     */
    ComponentDefinition();

    /*!
     * @details
     *   Initialises a new instance of the ComponentDefinition class using
     *   specified component and IComponentDefinition::Enabled availability.
     *
     *   If availability was changed during last application's start, it will be
     *   loaded and ovewrite default value.
     */
    ComponentDefinition(const QString &componentName);

    ~ComponentDefinition();

public slots:
    void addParent(const QString &parent);

    /*!
     * @details
     *   Gets the value specified whether this component is enabled, disabled, or unavailable.
     *   When the availability is enabled, the component is checked in the Components dialog.
     * @sa setAvailability
     */
    Availability availability() const;

    /*!
     * @details
     *   Returns the defined component.
     */
    IComponent *component() const;

    /*!
     * @details
     *   Returns the component location (for loaded components). It might be absolute or
     *   relative path.
     *
     *   Returns empty string for explicitly loaded components (static components).
     */
    const QString &componentLocation() const;

    /*!
     * @details
     *   Returns the component name.
     */
    const QString &componentName() const;

    /*!
     * @details
     *   Gets the detailed description text that is displayed for this component in the
     *   About this component box in the Components dialog.
     */
    const QString &description() const;

    /*!
     * @details
     *   Loads component availability using QSettings and component name.
     */
    void loadAvailability();

    /*!
     * @details
     *   Gets the list of parent (dependent) components names.
     */
    const QStringList &parents() const;

    /*!
     * @details
     *   Gets the the name that is displayed for this component in the Components dialog.
     */
    const QString &productName() const;

    /*!
     * @details
     *   Sets the value specified whether this component is enabled or disabled.
     *   The checked state of the component is saved in the user settings.
     * @sa availability
     */
    void setAvailability(Availability i_newMode);

    void setComponent(IComponent *component);

    /*!
     * @details
     *   Sets the component description.
     */
    void setComponentName(const QString &name);

    /*!
     * @details
     *   Sets the component description.
     */
    void setDescription(const QString &description);

    /*!
     * @details
     *   Sets the product name.
     */
    void setProductName(const QString &productName);

    /*!
     * @details
     *   Sets the component location.
     */
    void setComponentLocation(const QString &componentLocation);

protected:
    /*!
     * @details
     *   This method emits availabilityChanged() signal when extension's
     *   availability changed.
     * @sa setAvailability, availabilityChanged
     */
    virtual void onAvailabilityChanged(Availability i_newMode);

private:
    Q_DISABLE_COPY(ComponentDefinition)

private:
    IComponent *mp_component;
    Availability m_availability;
    QString m_componentName;
    QString m_description;
    QString m_productName;
    QString m_componentLocation;
    QStringList m_parents;
};

#endif // COMPONENTDEFINITION_H
