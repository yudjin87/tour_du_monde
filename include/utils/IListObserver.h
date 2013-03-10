#ifndef ILISTOBSERVER_H
#define ILISTOBSERVER_H

template <typename TItem> struct Changes;

/*!
 * @brief
 *   This class defines observer's interface for the notifications
 *   from the ObservableList.
 * @details
 *   You have to implement this interface to listen ObservableList's
 *   changes.
 */
template <typename TItem>
class IListObserver
{
public:
    /*!
     * @details
     *   This method is invoked by the ObservableList when it is changed:
     *   items were added, removed, or it was sorted, etc.
     *
     *   Use @a changes to obtain more details about incoming changes.
     */
    virtual void onChanged(const Changes<TItem> &changes) = 0;
};

#endif // ILISTOBSERVER_H
