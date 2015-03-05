/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2015 Carousel team
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

#ifndef SYMBOLWIDGET_H
#define SYMBOLWIDGET_H

#include <display/display_api.h>
#include <geometry/GeometryType.h>

#include <QtWidgets/QWidget>

class ISymbol;
class QLabel;

class DISPLAY_API SymbolWidget : public QWidget
{
    Q_OBJECT
public:
    SymbolWidget(const GeometryType type, QWidget *parent = nullptr);
    ~SymbolWidget();

    virtual const ISymbol* symbol() const = 0;
    virtual bool wasChanged() const = 0;
    void initializeSample();

    virtual void prepareForEmbedding() = 0;

signals:
    void symbolChanged(const ISymbol* newSymbol);

protected:
    virtual void insertSampleWidget(QWidget* sample) = 0;
    virtual ISymbol* symbol() = 0;

private slots:
    void onSymbolChanged(const ISymbol* newSymbol);
    void updateSample();

protected:
    const int LABEL_COLUMN_WIDHT = 50; // have to synchronoze embedded widgets, because of 1st column width may be different

private:
    const GeometryType m_type;
    QLabel* m_sample;
};

#endif // SYMBOLWIDGET_H
