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

#ifndef TYPECREATORS_H
#define TYPECREATORS_H

#include <carousel/utils/IServiceLocator.h>

template <typename TType>
class TypeBuilder
{
public:
    typedef TType InstantiatedType;
public:
    TypeBuilder(IServiceLocator *serviceLocator) : m_serviceLocator(serviceLocator) {}

    TType* getObject()
    {
        TType* result = m_serviceLocator->buildInstance<TType>();
        return result;
    }

private:
    IServiceLocator *m_serviceLocator;
};

template <typename TType>
class TypeLocator
{
public:
    typedef TType InstantiatedType;
public:
    TypeLocator(IServiceLocator *serviceLocator) : m_serviceLocator(serviceLocator) {}

    TType* getObject()
    {
        TType* result = m_serviceLocator->locate<TType>();
        return result;
    }

private:
    IServiceLocator *m_serviceLocator;
};

template<typename ... TToCreate>
class TypeCreator;

// TODO: use variadic templates
// TODO: documentation
template<typename TToCreate, typename TReq1>
class TypeCreator<TToCreate, TReq1>
{
public:
    TypeCreator(IServiceLocator *serviceLocator)
        : m_serviceLocator(serviceLocator)
    {
    }

    void* operator()()
    {
        TReq1::InstantiatedType* req1 = TReq1(m_serviceLocator).getObject();
        TToCreate* result = new TToCreate(req1);
        return result;
    }

private:
    IServiceLocator *m_serviceLocator;
};

template<typename TToCreate, typename TReq1, typename TReq2>
class TypeCreator<TToCreate, TReq1, TReq2>
{
public:
    TypeCreator(IServiceLocator *serviceLocator)
        : m_serviceLocator(serviceLocator)
    {
    }

    void* operator()()
    {
        TReq1::InstantiatedType* req1 = TReq1(m_serviceLocator).getObject();
        TReq2::InstantiatedType* req2 = TReq2(m_serviceLocator).getObject();
        TToCreate* result = new TToCreate(req1, req2);
        return result;
    }

private:
    IServiceLocator *m_serviceLocator;
};

template<typename TToCreate, typename TReq1, typename TReq2, typename TReq3>
class TypeCreator<TToCreate, TReq1, TReq2, TReq3>
{
public:
    TypeCreator(IServiceLocator *serviceLocator)
        : m_serviceLocator(serviceLocator)
    {
    }

    void* operator()()
    {
        TReq1::InstantiatedType* req1 = TReq1(m_serviceLocator).getObject();
        TReq2::InstantiatedType* req2 = TReq2(m_serviceLocator).getObject();
        TReq3::InstantiatedType* req3 = TReq3(m_serviceLocator).getObject();
        TToCreate* result = new TToCreate(req1, req2, req3);
        return result;
    }

private:
    IServiceLocator *m_serviceLocator;
};

#endif // TYPECREATORS_H
