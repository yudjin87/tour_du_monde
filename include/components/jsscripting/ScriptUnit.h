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

class JSSCRIPTING_API ScriptUnit : public IScriptUnit
{
    Q_OBJECT
    typedef QScopedPointer<QScriptEngine> QScriptEnginePtr;

public:
    /*!
     *
     */
    ScriptUnit(IScriptEngineFactory *factory, QObject *parent = nullptr);
    ScriptUnit(const QString &filePath, IScriptEngineFactory *factory, QObject *parent = nullptr);
    ~ScriptUnit();

public:
    bool isLoaded() const;

    QString absoluteFilePath() const;

    QString fileName() const;

    QString scriptText() const;
    void setScriptText(const QString &plainText);
    QTextDocument *script();
    const QTextDocument *script() const;

    void print(const QString &message);

public slots:
    bool load();
    bool load(const QString &filePath);
    void clear();
    bool save();
    bool saveAs(const QString &filePath);
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
