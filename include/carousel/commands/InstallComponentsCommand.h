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

#ifndef INSTALLCOMPONENTSCOMMAND_H
#define INSTALLCOMPONENTSCOMMAND_H

#include <carousel/carousel_global.h>
#include <carousel/commands/BaseUndoableCommand.h>

#include <QtCore/QStringList>

class IComponent;
class IComponentManager;

class CAROUSEL_API InstallComponentsCommand : public BaseUndoableCommand
{
    Q_OBJECT
public:
    InstallComponentsCommand(IUndoStack *stack, IComponentManager *manager, QObject* parent = nullptr);
    ~InstallComponentsCommand();

    void redo() override;
    void undo() override;

public slots:
    void addDefinitionPath(const QString &definitionPath);

    void setInstallPath(const QString &installPath);
    const QString &installPath() const;

    void setSourceDirectoryPath(const QString &sourceDirectoryPath);
    const QString &sourceDirectoryPath() const;

    bool addComponentsAfterInstallation() const;
    void setAddComponentsAfterInstallation(bool start);

    bool startComponentsAfterInstallation() const;
    void setStartComponentsAfterInstallation(bool start);

    bool tryRedo();

private:
    IComponentManager *m_manager;
    QString m_sourceDirectoryPath;
    QString m_installPath;
    QStringList m_definitionFiles;
    QList<IComponent *> m_installedComponents;
    bool m_addAfterInstallation;
    bool m_startAfterInstallation;
};

#endif // INSTALLCOMPONENTSCOMMAND_H
