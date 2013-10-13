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

#ifndef PERSISTENCESERVICE_H
#define PERSISTENCESERVICE_H

#include <components/persistence/IPersistenceService.h>

class IServiceLocator;
class IComponentManager;

/*!
 * @brief
 */
class PERSISTENCE_API PersistenceService : public IPersistenceService
{
    Q_OBJECT
public:
    /*!
     * @details
     * @constructor{PersistenceService} using specified @a locator. This locator is used only
     *   to create default IPersistenceDelegate.
     */
    PersistenceService(IServiceLocator *locator, IComponentManager *manager, QObject *parent = nullptr);

    /*!
     * @details
     * @constructor{PersistenceService} using specified @a delegate.
     *
     *   Note, that it takes ownership for the @a delegate.
     */
    PersistenceService(IPersistenceDelegate *delegate, IComponentManager *manager, QObject *parent = nullptr);
    ~PersistenceService();

public:
    IPersistenceDelegate *delegate() override;
    const IPersistenceDelegate *delegate() const override;
    void setDelegate(IPersistenceDelegate *delegate) override;

    /*!
     * @details
     *   Gets the absolute path to the file from wich document was loaded.
     */
    QString absoluteFilePath() const override;

    /*!
     * @details
     *   Gets the file name from wich document was loaded.
     *
     * @sa QFileInfo::fileName, absoluteFilePath
     */
    QString fileName() const override;

public slots:
    /*!
     * @details
     *   Tries to save document to the filePath().
     *   Returns @a true, if saving was successful.
     */
    bool save() override;

    /*!
     * @details
     *   Tries to save document to a @a filePath.
     *   Sets @a filePath as a current file name and returns @a true, if saving was successful.
     *
     *   Since after successful saving file name is changed, the fileNameChanged() signal is
     *   emitted.
     */
    bool saveAs(const QString &filePath) override;

    /*!
     * @details
     *   Tries to load document from the filePath().
     *   Returns @a true, if loading was successful.
     */
    bool load() override;

    /*!
     * @details
     *   Tries to load document from a @a filePath.
     *   Sets @a filePath as a current file name and returns @a true, if loading was successful.
     *
     *   Since after successful loading file name is changed, the fileNameChanged() signal is
     *   emitted.
     */
    bool load(const QString &filePath) override;

protected:
    virtual bool saveToFile(const QString &filePath);

private:
    Q_DISABLE_COPY(PersistenceService)
    static QString absolutePath(const QString &filePath);

private:
    IPersistenceDelegate *m_delegate;
    IComponentManager *m_manager;
    QString m_filePath;
};

#endif // PERSISTENCESERVICE_H
