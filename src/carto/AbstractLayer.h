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
#include <carto/LayerType.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QRectF>
#include <memory>

class IDisplay;
class ILayerVisitor;

class CARTO_API AbstractLayer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QRectF extent READ extent)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool visibility READ isVisible WRITE setVisible NOTIFY visibilityChanged)
    Q_PROPERTY(double minimumScale READ minimumScale WRITE setMinimumScale NOTIFY minimumScaleChanged)
    Q_PROPERTY(double maximumScale READ maximumScale WRITE setMaximumScale NOTIFY maximumScaleChanged)
public:
    AbstractLayer(QObject *parent = nullptr);

    virtual void draw(IDisplay *display) = 0;

    virtual QRectF extent() const = 0;

    virtual LayerType type() const = 0;
    const QString &name() const; // TODO: displayName, because we have FeatureClass name which can't be changed
    void setName(const QString &name);

    bool isVisible() const;
    void setVisible(bool visible = true);

    double minimumScale() const;
    double maximumScale() const;

    void setMinimumScale(double minimumScale);
    void setMaximumScale(double maximumScale);

    virtual void accept(ILayerVisitor& visitor) = 0;

signals:
    void nameChanged(AbstractLayer* sender, const QString &newName);
    void visibilityChanged(AbstractLayer* sender, bool visible);
    void minimumScaleChanged(AbstractLayer* sender, double minimumScale);
    void maximumScaleChanged(AbstractLayer* sender, double maximumScale);

protected:
    virtual void hide() = 0;
    virtual void show() = 0;

private:
    QString m_name;
    bool m_isVisible;
    double m_minimumScale;
    double m_maximumScale;
};

typedef std::unique_ptr<AbstractLayer> AbstractLayerUPtr;
