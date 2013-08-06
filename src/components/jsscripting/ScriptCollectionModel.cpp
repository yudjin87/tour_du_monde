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

#include "ScriptCollectionModel.h"
#include "IScriptUnit.h"

#include <carousel/logging/LoggerFacade.h>
#include <carousel/utils/IServiceLocator.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptCollectionModel");
}

//------------------------------------------------------------------------------
ScriptCollectionModel::ScriptCollectionModel(IScriptCollection *data, QObject *parent)
    : QObject(parent)
    , m_data(data)
    , m_locator(nullptr)
{
    connect(m_data, &IScriptCollection::scriptAdded, this, &ScriptCollectionModel::scriptAdded);
    connect(m_data, &IScriptCollection::scriptRemoved, this, &ScriptCollectionModel::scriptRemoved);
}

//------------------------------------------------------------------------------
ScriptCollectionModel::~ScriptCollectionModel()
{
    m_locator = nullptr;
}

//------------------------------------------------------------------------------
void ScriptCollectionModel::injectServiceLocator(IServiceLocator *locator)
{
    m_locator = locator;
}

//------------------------------------------------------------------------------
IScriptCollection::Scripts ScriptCollectionModel::scripts() const
{
    return m_data->scripts();
}

//------------------------------------------------------------------------------
void ScriptCollectionModel::onLoad()
{
    QFileDialog fileDialog(m_locator->locate<QMainWindow>(), "Load script");
    fileDialog.setNameFilter("JavaScript Files (*.js)");
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setDirectory(QCoreApplication::applicationDirPath() + "/scripts");  // TODO: get last selected directory from settings
    if (!fileDialog.exec())
        return;

    // TODO: This should be moved to the separate command
    //      v   v   v   v   v
    QString selectedFile = fileDialog.selectedFiles().first();
    QFile scriptFile(selectedFile);
    if (!scriptFile.open(QIODevice::ReadOnly)) {
        QString error = QString("Selected file %1 could not be opened!").arg(selectedFile);
        Log.w(error);
        QMessageBox::warning(m_locator->locate<QMainWindow>(), "Error during opening file", error);
        return;
    }

    m_data->addScript(selectedFile);
}

//------------------------------------------------------------------------------
void ScriptCollectionModel::onSave(IScriptUnit *script)
{
    // for saveAs:
//    if (script->fileName().isEmpty()) {
//        QFileDialog fileDialog(m_locator->locate<QMainWindow>(), "Save script");
//        fileDialog.setNameFilter("JavaScript Files (*.js)");
//        fileDialog.setFileMode(QFileDialog::ExistingFile);
//        fileDialog.setDirectory(QCoreApplication::applicationDirPath() + "/scripts");  // TODO: get last selected directory from settings
//        if (!fileDialog.exec())
//            return;

//    }

    script->save();
}

//------------------------------------------------------------------------------
void ScriptCollectionModel::onSaveAll()
{

}

//------------------------------------------------------------------------------
bool ScriptCollectionModel::onRun(IScriptUnit *script, QString *output)
{
    return script->run(output);
}

//------------------------------------------------------------------------------
