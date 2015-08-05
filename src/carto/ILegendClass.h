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
#include <QtCore/QObject>
#include <QtCore/QString>
#include <memory>

class ISymbol;

class CARTO_API ILegendClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(ISymbol *symbol READ symbol WRITE setSymbol NOTIFY symbolChanged)
public:
    ILegendClass(){}
    virtual ~ILegendClass(){}

    virtual QString description() const = 0;
    virtual void setDescription(const QString& description) = 0;

    virtual QString label() const = 0;
    virtual void setLabel(const QString& label) = 0;

    virtual bool isVisible() const = 0;
    virtual void setVisible(const bool isVisible) = 0;

    virtual ISymbol* symbol() = 0;
    virtual const ISymbol* symbol() const = 0;
    virtual void setSymbol(ISymbol* symbol) = 0;

    virtual ILegendClass* clone() const = 0;

signals:
    void descriptionChanged(const QString& description);
    void labelChanged(const QString& description);
    void symbolChanged(const ISymbol* newSymbol);
    void visibilityChanged(bool isVisible);
};

typedef std::unique_ptr<ILegendClass> ILegendClassUPtr;
