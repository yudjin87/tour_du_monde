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

#pragma once
#include <components/persistence/persistence_global.h>

#include <QtCore/QObject>

class IPersistenceDelegate;

/*!
 * @brief
 */
class PERSISTENCE_API IPersistenceService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileNameChanged)
    Q_PROPERTY(QString absoluteFilePath READ absoluteFilePath NOTIFY fileNameChanged)
public:
    /*!
     * @details
     * @constructor{IPersistenceService}.
     */
    IPersistenceService(){}

public:
    virtual IPersistenceDelegate *delegate() = 0;
    virtual const IPersistenceDelegate *delegate() const = 0;
    virtual void setDelegate(IPersistenceDelegate *delegate) = 0;

    /*!
     * @details
     *   Gets the absolute path to the file from wich document was loaded.
     */
    virtual QString absoluteFilePath() const = 0;

    /*!
     * @details
     *   Gets the fileName name from wich document was loaded.
     *
     * @sa QFileInfo::fileName, absoluteFilePath
     */
    virtual QString fileName() const = 0;

public slots:
    /*!
     * @details
     *   Tries to save document to the filePath().
     *   Returns @a true, if saving was successful.
     */
    virtual bool save() = 0;

    /*!
     * @details
     *   Tries to save document to a @a filePath.
     *   Sets @a filePath as a current file name and returns @a true, if saving was successful.
     *
     *   Since after successful saving file name is changed, the fileNameChanged() signal is
     *   emitted.
     */
    virtual bool saveAs(const QString &filePath) = 0;

    /*!
     * @details
     *   Tries to load document from the filePath().
     *   Returns @a true, if loading was successful.
     */
    virtual bool load() = 0;

    /*!
     * @details
     *   Tries to load document from a @a filePath.
     *   Sets @a filePath as a current file name and returns @a true, if loading was successful.
     *
     *   Since after successful loading file name is changed, the fileNameChanged() signal is
     *   emitted.
     */
    virtual bool load(const QString &filePath) = 0;

signals:
    /*!
     * @details
     *   This signal is emitted when document's file name is changed. It could happen
     *   on loading a new file or saving as a new file.
     *
     * @sa load(), saveAs()
     */
    void fileNameChanged();

private:
    Q_DISABLE_COPY(IPersistenceService)
};

