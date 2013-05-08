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

#ifndef IDIRECTORYCOMPONENTPROVIDER_H
#define IDIRECTORYCOMPONENTPROVIDER_H

#include "componentsystem/componentsystem_global.h"
#include "componentsystem/IComponentProvider.h"

#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QString>

/*!
 * @brief
 *   The IDirectoryComponentProvider uses to load custom components from the specified
 *   library path.
 * @details
 *   IDirectoryComponentProvider does not instantiate components from the shared libraries,
 *   it uses FileComponentProvider instead.
 *
 *   To export your component in shared library you have to define it:
 *
 * @code
 *   #include <componentsystem/BaseComponent.h>
 *
 *   class MyComponent : public BaseComponent
 *   {
 *       Q_OBJECT
 *   public:
 *       MyComponent(QObject *parent = nullptr);
 *   protected:
 *       bool onStartup(QObject *initData);
 *   private:
 *       AbstractApplication *m_app;
 *   };
 * @endcode
 *
 *   and to export it in @a MyComponent.cpp file using macros EXPORT_COMPONENT:
 *
 * @code
 *   #include "MyComponent.h"
 *   #include <componentsystem/ComponentExport.h>
 *
 *   MyComponent::MyComponent(QObject *parent)
 *      : BaseComponent("MyComponent", parent)
 *      , m_app(nullptr)
 *   {
 *   }
 *
 *   bool MyComponent::onStartup(QObject *initData)
 *   {
 *       m_app = dynamic_cast<AbstractApplication *>(initData);
 *       return (m_app != nullptr);
 *   }
 *
 *   EXPORT_COMPONENT(MyComponent)
 *
 * @endcode
 *
 *   You also should provide definition for the component:
 *
 * @code
 *   <component name="MyComponent">
 *       <productName>My super product</productName>
 *       <description>Ultra feature</description>
 *       <location>./MyComponent</location>
 *       <parents>
 *           <parentComponent name="ComponentA"/>
 *           <parentComponent name="ComponentC"/>
 *           <parentComponent name="ComponentB"/>
 *       </parents>
 *   </component>
 * @endcode
 *
 *   XmlDefinitionParser will be used to read this meta-information, by which ProxyComponent
 *   should load the real component.
 *
 *   Then you should override BootloaderBase::createComponentProvider() to return
 *   IDirectoryComponentProvider pointer or BootloaderBase::configureComponentProvider()
 *   to specify path for the library:
 * @code
 *   IComponentProvider *MyBootloader::createComponentProvider()
 *   {
 *       return new DirectoryComponentProvider("plugins/");
 *   }
 *   void MyBootloader::configureComponentProvider()
 *   {
 *       static_cast<IDirectoryComponentProvider *>(m_componentProvider)->setPath("plugins/");
 *   }
 * @endcode
 *   During boot loading sequence IDirectoryComponentProvider will find all component
 *   definitions in the @a plugins/ directory and instantiate proxy components for them,
 *   which creates real components by demand.
 * @note it does not take ownership neither for proxy components that will be @a discovered in
 *   libraries nor for components registered by registerComponent().
 */
class COMP_API IDirectoryComponentProvider : public IComponentProvider
{
    Q_OBJECT
public:
    IDirectoryComponentProvider(){}
    ~IDirectoryComponentProvider(){}

public:
   /*!
    * @details
    *   Sets the root directory path containing component definitions.
    */
   virtual void setPath(const QString &path) = 0;

   /*!
    * @details
    *   Sets the definition files extension "*.definition" is by default.
    */
   virtual void setExtension(const QString &definitionExtension) = 0;

   /*!
    * @details
    *   Sets the filters for searching files in the specified path.
    *
    *   QDir::NoDotAndDotDot | QDir::Readable are by default.
    */
   virtual void setFilters(QDir::Filters filters) = 0;

   /*!
    * @details
    *   Sets the flag for iterating over files in the specified path.
    *
    *   QDirIterator::Subdirectories is by default.
    */
   virtual void setFlags(QDirIterator::IteratorFlags flags) = 0;

   /*!
    * @details
    *   Gets the directory path containing component definitions.
    */
   virtual const QString &path() const = 0;

   /*!
    * @details
    *   Gets the definition files extension.
    */
   virtual const QString &extension() const = 0;

   /*!
    * @details
    *   Gets the filters for searching files in the specified path.
    */
   virtual QDir::Filters filters() const = 0;

   /*!
    * @details
    *   Gets the flag for iterating over files in the specified path.
    */
   virtual QDirIterator::IteratorFlags flags() const = 0;

   /*!
    * @details
    *   Loads definitions from the specified root path and tries to create
    *   proxy the components from them if they have not created yet.
    *
    *   Returns list of the new discovered components.
    */
   virtual QList<IComponent *> update() = 0;

private:
    Q_DISABLE_COPY(IDirectoryComponentProvider)
};

#endif // IDIRECTORYCOMPONENTPROVIDER_H
