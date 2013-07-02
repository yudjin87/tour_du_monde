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

#ifndef COMPONENTDEPENDENCIESTEST_H
#define COMPONENTDEPENDENCIESTEST_H

#include <QtCore/QObject>

class ComponentDependenciesTest : public QObject
{
    Q_OBJECT
public:
    ComponentDependenciesTest(QObject *parent = 0);

private slots:
    void shouldAddComponent();
    void shouldnotAddExistedComponent();
    void shouldNotAddNullPointer();
    void shouldFindComponentByName();

    void shouldReturnResultWithCiclycFlag();

    void shouldGetParentsForComponent();
    void shouldGetDependingsForComponent();
    void shouldCompleteListWithTheirChildren();
    void shouldCompleteOrderedComponents();
    void shouldCompleteListWithChild();
    void shouldCompleteListWithParentsForOneComponent();
    void shouldCompleteListWithTheirParents();
    void shouldCompleteListWithFullParents();
    void shouldCompleteListWithParentsTransitively();
    void shouldNotAddExtraParentsToCompletedList();
    void shouldCompleteListWithTheirParent();

    void completeListWithTheirChildren_shouldAddMissedComponentsForIncompatibleOnes();
    void completeListWithTheirChildren_shouldAddMissedComponentsForTransitiveIncompatibleOnes();
};

#endif // COMPONENTDEPENDENCIESTEST_H
