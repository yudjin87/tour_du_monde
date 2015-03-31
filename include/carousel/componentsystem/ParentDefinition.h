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
#include <carousel/carousel_global.h>

#include <QtCore/QObject>
#include <QtCore/QString>

class Version;

/*!
 * @brief
 *   This class defines a parent component properties, required for the child startup.
 * @details
 *   They are component name and component version. The name is used for
 *   determine build order (parents should be started before their children),
 *   and the version is used to determine component compatibility.
 *
 *   Those properties should be declared on the definition file, e.g. for XML:
 * @code
 *    <component name="MyComponentId">
 *       <version>1.0</version>
 *       <parents>
 *           <parentComponent name="org.carousel.Interactivity" version="1.0"/>
 *       </parents>
 *    </component>
 * @endcode
 *
 *   or in the code (for static integration):
 * @code
 *    MyComponent::MyComponent(QObject *parent)
 *        : BaseComponent("MyComponentId", parent)
 *    {
 *        setVersion(1, 0);
 *        addParent("org.carousel.Interactivity", 1, 0);
 *    }
 * @endcode
 *
 * @sa ComponentDefinition::parents()
 */
class CAROUSEL_API ParentDefinition : public QObject
{
    Q_OBJECT

    /*!
     * @details
     *   Gets a name of the parent component. This name is used to deternime startup order
     *   for child components.
     * @accessors name()
     */
    Q_PROPERTY(QString name READ name)

    /*!
     * @details
     *   Gets a version of the parent component. It is used to deternime compatibility
     *   for child components.
     * @accessors version()
     */
    Q_PROPERTY(const Version* version READ version)

public:
    /*!
     * @details
     * @constructor{ParentDefinition} using specified component name and
     *   with parent object @a parent. It also sets @a version to 1.0 by default.
     */
    explicit ParentDefinition(const QString &name, QObject *parent = nullptr);

    /*!
     * @details
     * @constructor{ParentDefinition} using specified component name and
     *   version. Note, that it takes ownership for the @a version.
     */
    ParentDefinition(const QString &name, Version *version, QObject *parent = nullptr);

    /*!
     * @details
     * @constructor{ParentDefinition} using specified component name and
     *   version.
     */
    ParentDefinition(const QString &name, int major_version, int minor_version, QObject *parent = nullptr);

    /*!
     * @details
     * @constructor{ParentDefinition} using specified component name and
     *   version.
     */
    ParentDefinition(const QString &name, int major_version, int minor_version, int build_version, QObject *parent = nullptr);

    /*!
     * @details
     * @constructor{ParentDefinition} using specified component name and
     *   version.
     */
    ParentDefinition(const QString &name, int major_version, int minor_version, int build_version, int revision_version, QObject *parent = nullptr);

    ~ParentDefinition();

    const QString &name() const;

    const Version *version() const;

private:
    Q_DISABLE_COPY(ParentDefinition)

private:
    QString m_name;
    Version *m_version;
};

