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

#ifndef CAROUSELPERSISTENCEDELEGATE_H
#define CAROUSELPERSISTENCEDELEGATE_H

#include <components/persistence/IPersistenceDelegate.h>

class IPersistExtension;
class IServiceLocator;

/*!
 * @brief
 */
class PERSISTENCE_API CarouselPersistenceDelegate : public IPersistenceDelegate
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{CarouselPersistenceDelegate}.
     */
    explicit CarouselPersistenceDelegate(IServiceLocator *locator, QObject *parent = nullptr);

    bool save(const QList<IComponent *> &components, QByteArray &saveStream) override;
    bool load(const QList<IComponent *> &components,  const QByteArray &loadStream) override;

protected:
    static IPersistExtension *extensionByName(const QList<IComponent *> &components, const QString &compName);
    IServiceLocator *locator();
    virtual bool saveExtension(IPersistExtension *extension, QJsonObject &toWrite);
    virtual bool loadExtension(IPersistExtension *extension, const QJsonObject &json);

private:
    Q_DISABLE_COPY(CarouselPersistenceDelegate)

private:
    IServiceLocator *m_locator;
};

#endif // CAROUSELPERSISTENCEDELEGATE_H
