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

#include "displayWidgets/PictureMarkerSymbolWidget.h"
#include <display/PictureMarkerSymbol.h>
#include "ui_PictureMarkerSymbolWidget.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileDialog>

PictureMarkerSymbolWidget::PictureMarkerSymbolWidget(const PictureMarkerSymbol* symbol, QWidget *parent)
    : SymbolWidget(Geometry::Type::Point, parent)
    , m_ui(new Ui::PictureMarkerSymbolWidget)
    , m_symbol(static_cast<PictureMarkerSymbol*>(symbol->clone()))
    , m_wasChanged(false)
{
    m_ui->setupUi(this);

    m_ui->picturePath->setText(m_symbol->source());
    connect(m_ui->selectFileBtn, &QAbstractButton::clicked, this, &PictureMarkerSymbolWidget::onSelectFileClicked);
}

PictureMarkerSymbolWidget::~PictureMarkerSymbolWidget()
{
    delete m_ui;
    m_ui = nullptr;
}

void PictureMarkerSymbolWidget::prepareForEmbedding()
{
    m_ui->verticalLayout->setContentsMargins(QMargins());
}

ISymbol *PictureMarkerSymbolWidget::symbol()
{
    return m_symbol.get();
}

void PictureMarkerSymbolWidget::onSelectFileClicked()
{
    QFileDialog fileDialog(this, "Select picture");
    fileDialog.setNameFilter("Images (*.png)");
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    if (m_ui->picturePath->text().isEmpty())
    {
        fileDialog.setDirectory(QCoreApplication::applicationDirPath());
    }
    else
    {
        QFileInfo dir(m_ui->picturePath->text());
        fileDialog.setDirectory(dir.absoluteDir().absolutePath());
        fileDialog.selectFile(m_ui->picturePath->text());
    }

    if (!fileDialog.exec())
        return;

    if (fileDialog.selectedFiles().empty())
        return;

    m_ui->picturePath->setText(fileDialog.selectedFiles().front());
    m_symbol->loadFromFile(fileDialog.selectedFiles().front());
    notifySymbolChanged();
}

void PictureMarkerSymbolWidget::notifySymbolChanged()
{
    m_wasChanged = true;
    emit symbolChanged(m_symbol.get());
}

const ISymbol *PictureMarkerSymbolWidget::symbol() const
{
    return m_symbol.get();
}

bool PictureMarkerSymbolWidget::wasChanged() const
{
    return m_wasChanged;
}

void PictureMarkerSymbolWidget::insertSampleWidget(QWidget *sample)
{
    const int SAMPLE_ROW = 1;
    QLabel* label = new QLabel(this);
    label->setText("Sample");
    m_ui->gridLayout->addWidget(label, SAMPLE_ROW, 0);
    m_ui->gridLayout->addWidget(sample, SAMPLE_ROW, 1);
}

