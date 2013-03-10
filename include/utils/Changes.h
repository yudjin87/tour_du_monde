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
    Changes<TItem>()
        : action(Reset)
    {
    }

    Changes<TItem>(ChangedAction action, const TItem &item)
        : action(action)
    {
        affectedItems.push_back(item);
    }

    Changes<TItem>(ChangedAction action, const QList<TItem> &items)
        : action(action)
        , affectedItems(items)
    {
    }

    ChangedAction action;
    QList<TItem> affectedItems;
};

#endif // CHANGES_H
