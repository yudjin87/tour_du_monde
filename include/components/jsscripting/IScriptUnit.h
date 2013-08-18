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
     *
     */
    IScriptUnit(){}

public:
    virtual bool isLoaded() const = 0;

    virtual QString absoluteFilePath() const = 0;

    virtual QString fileName() const = 0;

    virtual QString scriptText() const = 0;
    virtual void setScriptText(const QString &plainText) = 0;
    virtual QTextDocument *script() = 0;
    virtual const QTextDocument *script() const = 0;

public slots:
    virtual bool load() = 0;
    virtual bool load(const QString &filePath)  = 0;
    virtual void clear() = 0;
    virtual bool save() = 0;
    virtual bool saveAs(const QString &filePath) = 0;

    // TODO: should emit output instead of getting it
    virtual bool run() = 0;

signals:
    void fileNameChanged();
    void printed(const QString &message);
    void error(const QString &message);

private:
    Q_DISABLE_COPY(IScriptUnit)
};

#endif // ISCRIPTUNIT_H
