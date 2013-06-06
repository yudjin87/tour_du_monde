#ifndef CHANGES_H
#define CHANGES_H

#include <QtCore/QList>

// TODO: change to the class enum
/*!
 * @details
 *   This enum is used to describe action changed the ObservableList.
 */
enum ChangedAction
{
    /*!
     * @details
     *   The item or items have been added to the observable list.
     */
    Add = 0,

    /*!
     * @details
     *   The item or items have been removed from the observable list.
     */
    Remove,

    /*!
     * @details
     *   The observable list has been significantly changed: it's been cleared or sorted.
     */
    Reset
};

/*!
 * @brief
 *   The Changes class describes ObservableList's changes.
 * @details
 *   It contains changing action (Add, Remove, ...) and affected
 *   items.
 */
template <typename TItem>
struct Changes
{
    /*!
     * @details
     * @constructor{Changes} for @a TItem type.
     */
    Changes<TItem>()
        : action(Reset)
    {
    }

    /*!
     * @details
     * @constructor{Changes} for @a TItem type with specified action type @a action and affected @a item.
     */
    Changes<TItem>(ChangedAction action, const TItem &item)
        : action(action)
    {
        affectedItems.push_back(item);
    }

    /*!
     * @details
     * @constructor{Changes} for @a TItem type with specified action type @a action and affected @a items.
     */
    Changes<TItem>(ChangedAction action, const QList<TItem> &items)
        : action(action)
        , affectedItems(items)
    {
    }

    /*!
     * @details
     * Gets an action that triggered changes.
     */
    ChangedAction action;

    /*!
     * @details
     * Gets affected @a items.
     */
    QList<TItem> affectedItems;
};

#endif // CHANGES_H
