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

#ifndef ISCRIPTUNIT_H
#define ISCRIPTUNIT_H

#include <components/jsscripting/jsscripting_global.h>
#include <components/jsscripting/IOutputHandler.h>

#include <QtCore/QObject>

class QTextDocument;

/*!
 * @brief
 *   This abstract class represents a JavaScript unit that could
 *   be loaded from file and executed.
 * @details
 *   The IScriptCollection interface is a storage for that units
 *   so you usually should to get IScriptCollection reference to
 *   create or to get some script unit.
 *
 *   This class itself does not provide any GUI capabilities, indeed
 *   it is rendered using ScriptUnitView widget. Since script is stored
 *   as text inside the QTextDocument, it is possible to setup this
 *   document to widgets like QTextEdit. It allows to use all benefits
 *   like code highliting and undo/redo.
 *
 * @sa IScriptCollection, ScriptUnitView
 */
class JSSCRIPTING_API IScriptUnit : public QObject, public IOutputHandler
{
    Q_OBJECT
    Q_PROPERTY(bool isLoaded READ isLoaded)
    Q_PROPERTY(QString absoluteFilePath READ absoluteFilePath)
    Q_PROPERTY(QString fileName READ fileName)
    Q_PROPERTY(QString scriptText READ scriptText WRITE setScriptText)
    Q_PROPERTY(QTextDocument *script READ script)
public:
    /*!
     * @details
     * @constructor{IScriptUnit}.
     */
    IScriptUnit(){}

public:
    /*!
     * @details
     *   Returns @a true if script was loaded from the file.
     */
    virtual bool isLoaded() const = 0;

    /*!
     * @details
     *   Gets the absolute path to the file from wich script was loaded (if it was loaded).
     */
    virtual QString absoluteFilePath() const = 0;

    /*!
     * @details
     *   Gets the file name from wich script was loaded (if it was loaded).
     *
     * @sa QFileInfo::fileName, absoluteFilePath
     */
    virtual QString fileName() const = 0;

    /*!
     * @details
     *   Gets script as a plain text.
     */
    virtual QString scriptText() const = 0;

    /*!
     * @details
     *   Sets a new @a plainText as a script.
     */
    virtual void setScriptText(const QString &plainText) = 0;

    /*!
     * @details
     *   Gets script as a document.
     */
    virtual QTextDocument *script() = 0;

    /*!
     * @details
     *   Gets script as a document.
     */
    virtual const QTextDocument *script() const = 0;

public slots:    
    /*!
     * @details
     *   Tries to load script from the fileName().
     *   Returns @a true, if loading was successful.
     */
    virtual bool load() = 0;

    /*!
     * @details
     *   Tries to load script from a @a filePath.
     *   Sets @a filePath as a current file name and returns @a true, if loading was successful.
     */
    virtual bool load(const QString &filePath) = 0;

    /*!
     * @details
     *   Clears script body.
     */
    virtual void clear() = 0;

    /*!
     * @details
     *   Tries to load script from the fileName().
     *   Returns @a true, if loading was successful.
     */
    virtual bool save() = 0;
    virtual bool saveAs(const QString &filePath) = 0;

    virtual bool run() = 0;

signals:
    void fileNameChanged();
    void printed(const QString &message);
    void error(const QString &message);

private:
    Q_DISABLE_COPY(IScriptUnit)
};

#endif // ISCRIPTUNIT_H
