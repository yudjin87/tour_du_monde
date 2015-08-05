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

#include "cartoPersist/LegendGroupPersist.h"
#include "cartoPersist/LegendClassPersist.h"
#include <carto/LegendGroup.h>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QVariant>

LegendGroupPersist::LegendGroupPersist()
{
}

void LegendGroupPersist::save(QJsonObject &obj, const ILegendGroup &legend)
{
    obj.insert("heading", legend.heading());
    obj.insert("isEditable", legend.isEditable());
    obj.insert("isVisible", legend.isVisible());

    QJsonArray jsonLegends;
    for (const ILegendClassUPtr& legendClass : legend)
    {
        QJsonObject jsonLegendClass;
        LegendClassPersist legendClassPersist;
        legendClassPersist.save(jsonLegendClass, *legendClass);
        jsonLegends.append(jsonLegendClass);
    }
    obj.insert("classes", jsonLegends);
}

ILegendGroupUPtr LegendGroupPersist::load(const QJsonObject &obj, QString *error)
{
    if (obj.isEmpty())
    {
        if (error) *error = "LegendGroupPersist: empty object";
        return nullptr;
    }

    LegendGroupUPtr legend(new LegendGroup());

    const QString heading = obj.value("heading").toString();
    const bool isEditable = obj.value("isEditable").toBool();
    const bool isVisible = obj.value("isVisible").toBool();
    legend->setHeading(heading);
    legend->setEditable(isEditable);
    legend->setVisible(isVisible);

    const QJsonArray jsonLegendClasses = obj.value("classes").toArray();
    for (const QJsonValue value : jsonLegendClasses)
    {
        const QJsonObject jsonLegendClass = value.toObject();
        LegendClassPersist legendClassPersist;
        ILegendClassUPtr legendClass = legendClassPersist.load(jsonLegendClass, error);
        if (legendClass == nullptr)
        {
            return nullptr;
        }

        legend->addClass(legendClass.release());
    }

    return std::move(legend);
}

