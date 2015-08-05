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

#pragma once
#include <carto/carto_api.h>
#include <carto/ILegendClass.h>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <memory>
#include <vector>

class CARTO_API ILegendGroup : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString heading READ heading WRITE setHeading NOTIFY headingChanged)
    Q_PROPERTY(bool isEditable READ isEditable WRITE setEditable NOTIFY editableChanged)
    Q_PROPERTY(bool isVisible READ isVisible WRITE setVisible NOTIFY visibilityChanged)
    Q_PROPERTY(size_t classCount READ classCount)
public:
    typedef std::vector<const ILegendClassUPtr> ILegendClassVector;

public:
    ILegendGroup(){}
    virtual ~ILegendGroup(){}

    virtual QString heading() const = 0;
    virtual void setHeading(const QString& heading) = 0;

    virtual bool isEditable() const = 0;
    virtual void setEditable(const bool editable) = 0;

    virtual bool isVisible() const = 0;
    virtual void setVisible(const bool visible) = 0;

    virtual size_t classCount() const = 0;

    virtual ILegendGroup* clone() const = 0;

    virtual ILegendClassVector::const_iterator begin() const = 0;
    virtual ILegendClassVector::const_iterator end() const = 0;

public slots:
    virtual ILegendClass* getClass(const size_t index) = 0;
    virtual const ILegendClass* getClass(const size_t index) const = 0;

    virtual ILegendClass* getClass(const QString& label) = 0;
    virtual const ILegendClass* getClass(const QString& label) const = 0;

    virtual void addClass(ILegendClass* legendClass) = 0;
    virtual void insertClass(const int index, ILegendClass* legendClass) = 0;
    virtual void clearClasses() = 0;
    virtual void removeClass(ILegendClass *legendClass) = 0;
    virtual ILegendClass* takeClass(const int index) = 0;

signals:
    void headingChanged(const QString& heading);
    void editableChanged(const bool editable);
    void visibilityChanged(const bool visible);

    void classAdded(ILegendClass *legendClass, const size_t index);
    void classRemoved(ILegendClass *legendClass, const size_t index);

private:
    ILegendGroup(const ILegendGroup&) = delete;
    ILegendGroup& operator=(const ILegendGroup&) = delete;
};

typedef std::unique_ptr<ILegendGroup> ILegendGroupUPtr;
