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

#ifndef SCRIPTUNIT_H
#define SCRIPTUNIT_H

#include <components/jsscripting/IScriptUnit.h>

#include <QtCore/QScopedPointer>

class IScriptEngineFactory;
class QScriptEngine;

/*!
 * @brief
 *   It is a default implementation of the IScriptUnit interface.
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
class JSSCRIPTING_API ScriptUnit : public IScriptUnit
{
    Q_OBJECT
    typedef QScopedPointer<QScriptEngine> QScriptEnginePtr;

public:
    /*!
     * @details
     * @constructor{ScriptUnit} with empty script body and specified @a factory for QScriptEngine
     *   creation for the each run() call.
     *
     *   Call load(file) to load some script.
     */
    explicit ScriptUnit(IScriptEngineFactory *factory, QObject *parent = nullptr);

    /*!
     * @details
     * @constructor{ScriptUnit} with empty script body and specified @a factory for QScriptEngine
     *   creation for the each run() call.
     *
     *   Call load() to load script from the @a filePath.
     */
    ScriptUnit(const QString &filePath, IScriptEngineFactory *factory, QObject *parent = nullptr);
    ~ScriptUnit();

public:
    /*!
     * @details
     *   Returns @a true if script was loaded from the file.
     */
    bool isLoaded() const;

    /*!
     * @details
     *   Gets the absolute path to the file from wich script was loaded (if it was loaded).
     */
    QString absoluteFilePath() const;

    /*!
     * @details
     *   Gets the file name from wich script was loaded (if it was loaded).
     *
     * @sa QFileInfo::fileName, absoluteFilePath
     */
    QString fileName() const;

    /*!
     * @details
     *   Gets script as a plain text.
     */
    QString scriptText() const;

    /*!
     * @details
     *   Sets a new @a plainText as a script.
     */
    void setScriptText(const QString &plainText);

    /*!
     * @details
     *   Gets script as a document.
     */
    QTextDocument *script();

    /*!
     * @details
     *   Gets script as a document.
     */
    const QTextDocument *script() const;

public slots:
    /*!
     * @details
     *   Tries to load script from the fileName().
     *   Returns @a true, if loading was successful.
     */
    bool load();

    /*!
     * @details
     *   Tries to load script from a @a filePath.
     *   Sets @a filePath as a current file name and returns @a true, if loading was successful.
     *
     *   Since after successful loading file name is changed, the fileNameChanged() signal is
     *   emitted.
     */
    bool load(const QString &filePath);

    /*!
     * @details
     *   Clears script body.
     */
    void clear();

    /*!
     * @details
     *   Tries to save script to the fileName().
     *   Returns @a true, if saving was successful.
     */
    bool save();

    /*!
     * @details
     *   Tries to save script to a @a filePath.
     *   Sets @a filePath as a current file name and returns @a true, if saving was successful.
     *
     *   Since after successful saving file name is changed, the fileNameChanged() signal is
     *   emitted.
     */
    bool saveAs(const QString &filePath);

    /*!
     * @details
     *   Tries to save script to the fileName(). All print() functions called from the script
     *   will be emitted as printed() signal.
     *   Returns @a true, if script was evaluated without errors. Otherwise, returns false and
     *   emits the error() signal.
     */
    bool run();

protected:
    virtual bool saveToFile(const QString &filePath);

private:
    Q_DISABLE_COPY(ScriptUnit)
    static QString absolutePath(const QString &filePath);    

private:
    bool m_isLoaded;
    QString m_fileName;
    IScriptEngineFactory *m_factory;
    QTextDocument *m_script;
    QScriptEnginePtr m_engine;
};

#endif // SCRIPTUNIT_H
