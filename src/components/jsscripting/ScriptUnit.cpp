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

#include "ScriptUnit.h"

#include <carousel/logging/LoggerFacade.h>

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QTextStream>
#include <QtGui/QTextDocument>

//------------------------------------------------------------------------------
namespace
{
static LoggerFacade Log = LoggerFacade::createLogger("ScriptUnit");
}

//------------------------------------------------------------------------------
ScriptUnit::ScriptUnit(QObject *parent)
    : QObject()
    , m_isLoaded(false)
    , m_fileName("")
    , m_script(new QTextDocument(this))
{
    setParent(parent);
}

//------------------------------------------------------------------------------
ScriptUnit::ScriptUnit(const QString &filePath, QObject *parent)
    : QObject()
    , m_isLoaded(false)
    , m_fileName(absolutePath(filePath))
    , m_script(new QTextDocument(this))
{
    setParent(parent);
}

//------------------------------------------------------------------------------
ScriptUnit::~ScriptUnit()
{
}

//------------------------------------------------------------------------------
bool ScriptUnit::load()
{
    m_isLoaded = false;

    QFile scriptFile(m_fileName);
    if (!scriptFile.open(QIODevice::ReadOnly)) {
        QString error = QString("Selected file %1 could not be opened!").arg(m_fileName);
        Log.w(error);
        return false;
    }

    m_script->setPlainText(scriptFile.readAll());

    m_isLoaded = true;
    return m_isLoaded;
}

//------------------------------------------------------------------------------
bool ScriptUnit::load(const QString &filePath)
{
    m_fileName = absolutePath(filePath);
    return load();
}

//------------------------------------------------------------------------------
void ScriptUnit::clear()
{
    m_script->clear();
}

//------------------------------------------------------------------------------
bool ScriptUnit::save()
{
    if (!m_script->isModified())
        return true;

    if (!saveToFile(m_fileName))
        return false;

    m_script->setModified(false);
    return true;
}

//------------------------------------------------------------------------------
bool ScriptUnit::saveAs(const QString &fileName)
{
    if (!saveToFile(fileName))
        return false;

    m_fileName = absolutePath(fileName);
    return true;
}

//------------------------------------------------------------------------------
bool ScriptUnit::isLoaded() const
{
    return m_isLoaded;
}

//------------------------------------------------------------------------------
QString ScriptUnit::fileName() const
{
    QFileInfo file(m_fileName);
    return file.fileName();
}

//------------------------------------------------------------------------------
QString ScriptUnit::scriptText() const
{
    return m_script->toPlainText();
}

//------------------------------------------------------------------------------
QString ScriptUnit::absoluteFilePath() const
{
    return m_fileName;
}

//------------------------------------------------------------------------------
QTextDocument *ScriptUnit::script()
{
    return m_script;
}

//------------------------------------------------------------------------------
const QTextDocument *ScriptUnit::script() const
{
    return m_script;
}

//------------------------------------------------------------------------------
QString ScriptUnit::absolutePath(const QString &filePath)
{
    QFileInfo file(filePath);
    return file.absoluteFilePath();
}

//------------------------------------------------------------------------------
bool ScriptUnit::saveToFile(const QString &filePath)
{
    QFile scriptFile(filePath);
    if (!scriptFile.open(QIODevice::WriteOnly)) {
        QString error = QString("Selected file %1 could not be opened!").arg(m_fileName);
        Log.w(error);
        return false;
    }

    QTextStream out(&scriptFile);
    out << scriptText();
    return true;
}

//------------------------------------------------------------------------------
