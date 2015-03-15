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

#ifndef IDIALOGSERVICE_H
#define IDIALOGSERVICE_H

#include "interactivity_global.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtWidgets/QDialog>

#include <typeinfo>

class QWidget;
struct IDialogConstructor;
class IServiceLocator;
class PropertiesDialog;
class PropertiesWidget;

/*!
 * @brief
 *   Defines methods for showing the dialogs.
 * @details
 *   Use IDialogService to show dialogs instead of explicitly creating dialogs
 *   in code to be able to fake dialogs (and returning results), e.g. for unit testing.
 *
 *   It is registered into the application services by the InteractionServiceComponent.
 */
class INTERACTIVITY_API IDialogService : public QObject
{
    Q_OBJECT
public:
    IDialogService(){}
    virtual ~IDialogService(){}

    /*!
     * @details
     *   Creates and returns a new instance of the dialog, if any was registered for
     *   the @a TDialogModel. Otherwise, returns @a nullptr.
     *
     *   Note, that created dialog will be set with Qt::WA_DeleteOnClose flag;
     *
     * @param TDialogModel the type of dialog model.
     *
     * @sa registerDialog(), showDialog()
     */
    template<typename TDialogModel>
    QDialog *createDialog(TDialogModel *dlgModel) const;

    /*!
     * @details
     *   Creates and returns a new instance of the dialog, setting @a mainWidget to its layout.
     *
     *   Note, that created dialog will be set with Qt::WA_DeleteOnClose flag;
     *   Created dialog will take ownership for @a mainWidget
     */
    virtual PropertiesDialog* createPropertyDialog(PropertiesWidget* mainWidget, QWidget* parentWindow = nullptr) const = 0;

    /*!
     * @details
     *   Returns @a true if dialog for the specified model type has been already
     *   registered.
     *   Otherwise, returns @a false.
     * @sa registerDialog(), unregisterDialogForModel()
     */
    template<typename TDialogModel>
    bool isRegistered() const;

    /*!
     * @details
     *   Registers the @a TDialog type, that expects a @a TDialogModel pointer
     *   in the constructor. This dialog will be shown from the showDialog() method.
     *
     *   A new @a TDialog type is pushed to the top of dialog stack for the specified
     *   @a TDialogModel type, so to use older dialogs for this model, you should
     *   pop newer dialog type by calling unregisterDialogForModel().
     *
     *   The model should be derived from the QObject (dirctly or indirectly)
     *   and it should implement method
     * @code
     *   void injectServiceLocator(IServiceLocator *locator);
     * @endcode
     *
     * @param TDialog the type of dialog.
     * @param TDialogModel the type of dialog model.
     * @note the @a TDialog should take ownership of the @a TDialogModel.
     *
     * @sa unregisterDialogForModel()
     */
    template<typename TDialog, typename TDialogModel>
    void registerDialog();

    /*!
     * @details
     *   Creates new instance of the dialog (if any was registered for
     *   the @a TDialogModel), opens a modal dialog and returns @a true
     *   if user accept it, otherwise @a false. Also returns @a false,
     *   if dialog was not registered for the @a TDialogModel.
     *
     *   This method was added for convinient, and it uses createDialog() inside.
     *
     * @param TDialogModel the type of dialog model.
     *
     * @sa registerDialog(), createDialog()
     */
    template<typename TDialogModel>
    bool showDialog(TDialogModel *dlgModel) const;

    /*!
     * @details
     *   Unregisters (pops) last registered dialog (that had to display model) for the
     *   specified model type @a TDialogModel.
     *
     *   Component, that is going to shut down, should unregister all dialogs
     *   to restore old ones (if any were).
     *
     *   Returns @a true if dialog for the specified model type has been registered.
     *   Otherwise, returns @a false.
     * @sa registerDialog()
     */
    template<typename TDialogModel>
    bool unregisterDialogForModel();

protected:
    /*!
     * @details
     *   When overridden creates a new instance of the registered dialog with
     *   specified model, using @a constructor.
     *
     *   This method is invoked from the showDialogForModel().
     * @sa showDialogForModel()
     */
    virtual QDialog *createDialogForModel(const QString &forDlgModelType, void *dlgModel) const = 0;

    /*!
     * @details
     *   When overridden returns @a true if dialog for the specified model type has
     *   been already registered.
     *   Otherwise, returns @a false.
     */
    virtual bool isConstructorRegistered(const QString &forDlgModelType) const = 0;

    /*!
     * @details
     *   When overridden registers the specified dialog constructor with the
     *   model type name for the creating dialog by demand (by the passed
     *   model type name).
     *
     *   This method is invoked from the template registerDialog() method,
     *   which gets model type name from the template model, and specializes
     *   dialog constructor with specified dialog and model types.
     * @sa showDialog(), registerDialog()
     */
    virtual void registerConstructor(const QString &dlgModelType, IDialogConstructor *constructor) = 0;

    /*!
     * @details
     *   When overridden creates a new instance of the registered dialog with
     *   specified model, shows it and returns closing code.
     *   If dialog was not registered for this model type,
     *   returns @a false.
     * @sa showDialog()
     */
    virtual bool showDialogForModel(const QString &forDlgModelType, void *dlgModel) const = 0;

    /*!
     * @details
     *   When overridden removes dialog constructor for the specified model type.
     *
     *   Returns @a true if dialog constructor for the specified model type has been registered.
     *   Otherwise, returns @a false.
     * @sa registerDialog()
     */
    virtual bool unregisterConstructor(const QString &forDlgModelType) = 0;

private:
    Q_DISABLE_COPY(IDialogService)
};

/*!
 * @brief
 *   Common interface for the dialog factory.
 */
struct IDialogConstructor
{
    virtual ~IDialogConstructor(){}

    /*!
     * @details
     *   Returns new instance of the dialog,
     *   and initializes it with parent window (for the default location)
     *   and dlgModel.
     */
    virtual void *create(void *dlgModel, QWidget *mainWindow) = 0;

    /*!
     * @details
     *   Sets a @a locator wich will be set to the model during
     *   dialog creation.
     */
    virtual void injectServiceLocator(IServiceLocator *locator) = 0;
};

/*!
 * @brief
 *   Generic class for the dialog factory.
 */
template<typename TDialog, typename TDialogModel>
struct DialogConstructor : public IDialogConstructor
{
    DialogConstructor()
    {
        static_assert(std::is_base_of<QObject, TDialogModel>::value, "TDialogModel should derive from the QObject!");
        static_assert(std::is_base_of<QDialog, TDialog>::value, "TDialog should derive from the QDialog!");
    }

    /*!
     * @details
     *   Returns new instance of the dialog,
     *   and initializes it with parent window (for the default location)
     *   and dlgModel.
     */
    void *create(void *dlgModel, QWidget *mainWindow)
    {
        QObject *obj = reinterpret_cast<QObject *>(dlgModel);
        TDialogModel *model = dynamic_cast<TDialogModel *>(obj);
        model->injectServiceLocator(m_locator);
        return new TDialog(model, mainWindow);
    }

    /*!
     * @details
     *   Sets a @a locator wich will be set to the model during
     *   dialog creation.
     */
    void injectServiceLocator(IServiceLocator *locator)
    {
        m_locator = locator;
    }

private:
    IServiceLocator *m_locator;
};

template<typename TDialogModel>
QDialog *IDialogService::createDialog(TDialogModel *dlgModel) const
{
    static_assert(std::is_base_of<QObject, TDialogModel>::value, "TDialogModel should derive from the QObject!");

    const QString &dlgModelType = typeid(TDialogModel).name();
    return createDialogForModel(dlgModelType, dlgModel);
}

template<typename TDialogModel>
bool IDialogService::isRegistered() const
{
    static_assert(std::is_base_of<QObject, TDialogModel>::value, "TDialogModel should derive from the QObject!");

    const QString &dlgModelType = typeid(TDialogModel).name();
    return isConstructorRegistered(dlgModelType);
}

template<typename TDialog, typename TDialogModel>
void IDialogService::registerDialog()
{
    static_assert(std::is_base_of<QObject, TDialogModel>::value, "TDialogModel should derive from the QObject!");
    static_assert(std::is_base_of<QDialog, TDialog>::value, "TDialog should derive from the QDialog!");

    const QString &dlgModelType = typeid(TDialogModel).name();
    registerConstructor(dlgModelType, new DialogConstructor<TDialog, TDialogModel>());
}

template<typename TDialogModel>
bool IDialogService::showDialog(TDialogModel *dlgModel) const
{
    static_assert(std::is_base_of<QObject, TDialogModel>::value, "TDialogModel should derive from the QObject!");

    const QString &dlgModelType = typeid(TDialogModel).name();
    return showDialogForModel(dlgModelType, dlgModel);
}

template<typename TDialogModel>
bool IDialogService::unregisterDialogForModel()
{
    static_assert(std::is_base_of<QObject, TDialogModel>::value, "TDialogModel should derive from the QObject!");

    const QString &dlgModelType = typeid(TDialogModel).name();
    return unregisterConstructor(dlgModelType);
}

#endif // IDIALOGSERVICE_H
