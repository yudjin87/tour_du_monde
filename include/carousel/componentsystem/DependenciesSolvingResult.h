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

#ifndef DEPENDENCIESSOLVINGRESULT_H
#define DEPENDENCIESSOLVINGRESULT_H

#include <carousel/carousel_global.h>

#include <QtCore/QStringList>
#include <QtCore/QList>

class IComponent;

/*!
 * @brief
 *   This class provides methods to obtain component dependencies solving result.
 * @details
 *   It contains a list of the ordered componetns - they were resolved succesfully;
 *   the list of the orphans - components those parents were not added to the solver;
 *   the list of the missing components. It also contains flag specified whether
 *   cyclic dependencis between components were found or not.
 *
 *   The instance of the DependenciesSolvingResult class is read-only value object.
 */
class CAROUSEL_API DependenciesSolvingResult
{
public:
    //TODO: move constructor for this value object

    /*!
     * @details
     *   Initializes a new instance of the DependenciesSolvingResult class with ordered
     *   components if any. Otherwise - empty instance.
     */
    explicit DependenciesSolvingResult(const QList<IComponent *> &ordered = QList<IComponent *>());

    /*!
     * @details
     *   Initializes a new instance of the DependenciesSolvingResult class with ordered,
     *   orphan, missing component names and the list of components which take part
     *   in the dependency solving.
     */
    DependenciesSolvingResult(QStringList &ordered, QStringList &orphans, QStringList &missing, const QList<IComponent *> &components, bool hasCyclic = false);

    /*!
     * @details
     *   Initializes a new instance of the DependenciesSolvingResult class using already
     *   existed instance.
     */
    DependenciesSolvingResult(const DependenciesSolvingResult &other);
    ~DependenciesSolvingResult();

    /*!
     * @details
     *   Initializes an existing or creates and initializes a new instance of the
     *   DependenciesSolvingResult class using already existed instance.
     */
    const DependenciesSolvingResult &operator=(const DependenciesSolvingResult &other);

    /*!
     * @details
     *   Returns @a true if at least one cyclic dependency has been found during resolving.
     *   Otherwise, returns @a false.
     *
     * @a false by default.
     */
    bool hasCyclicDependencies() const;

    /*!
     * @details
     *   Returns list of missing component names. Those parent components
     *   were required during resolving, but they were not added to the
     *   solver.
     *
     * @sa orphans()
     */
    QStringList missing() const;

    /*!
     * @details
     *   Returns list of resolved components. The order of components depends of
     *   the resolving operation.
     */
    QList<IComponent *> ordered() const;

    /*!
     * @details
     *   Returns list of orphan components. They parents were missing during
     *   resolving.
     *
     * @sa missing()
     */
    QList<IComponent *> orphans() const;

private:
    static bool precidate(IComponent *component, const QString &name);
    void collectComponents(const QStringList &names, QList<IComponent *> &result) const;

private:
    QStringList m_orderedNames;
    QStringList m_orphansNames;
    QStringList m_missingNames;
    QList<IComponent *> m_components;
    mutable QList<IComponent *> m_orphans;
    mutable QList<IComponent *> m_ordered;
    bool m_hasCyclic;
};

#endif // DEPENDENCIESSOLVINGRESULT_H
