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

#ifndef DIALOGSERVICE_H
#define DIALOGSERVICE_H

#include "IDialogService.h"

#include <QtCore/QMap>

class QDialog;
class QWidget;

/*!
 * @brief
 *   Defines methods for showing the dialogs.
 * @details
 *   Use IDialogService to show dialogs instead of explicitly creating dialogs
 *   in code to be able to fake dialogs (and returning results), e.g. for unit testing.
 *
 *   It is registered into the application services by the InteractionServiceComponent.
 */
class INTERACTIVITY_API DialogService : public IDialogService
{
    Q_OBJECT
public:
    DialogService(QWidget *mainWindow, IServiceLocator *locator);
    ~DialogService();

protected:
    /*!
     * @details
     *   Registers the specified dialog constructor with the
     *   model type name for the creating dialog by demand (by the passed
     *   model type name).
     *
     *   This method is invoked from the template registerDialog() method,
     *   which gets model type name from the template model, and specializes
     *   dialog constructor with specified dialog and model types.
     * @sa showDialog(), registerDialog()
     */
    void registerConstructor(const QString &dlgModelType, IDialogConstructor *constructor);

    /*!
     * @details
     *   Creates dialog, shows it and returns closing code.
     *   If dialog was not registered for this model type,
     *   returns @a false.
     * @sa showDialog()
     */
    bool showDialogForModel(const QString& forDlgModelType, void *dlgModel) const;

    /*!
     * @details
     *   Creates a new instance of the registered dialog with
     *   specified model, using @a constructor.
     *
     *   This method is invoked from the showDialogForModel().
     * @sa showDialogForModel()
     */
    virtual QDialog *createDialog(IDialogConstructor *constructor, void *dlgModel) const;

private:
    /*!
     * @details
     *    The map between dialog types and their constructors.
     */
    QMap<QString, IDialogConstructor *> m_viewsMap;

    /*!
     * @details
     *   The main window used as owner for dialogs.
     */
    QWidget *m_mainWindow;

    IServiceLocator *m_locator;
};

#endif // DIALOGSERVICE_H
