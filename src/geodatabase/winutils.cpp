/* BEGIN_COMMON_COPYRIGHT_HEADER
 * (c)LGPL2+
 *
 * Carousel - Qt-based managed component library.
 *
 * Copyright: 2011-2016 Carousel team
 * Authors:
 *   Yevhen Chuhui (Eugene Chuguy) <yevhen.chuhui@gmail.com>
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

#include "geodatabase/winutils.h"

#ifdef Q_OS_WIN32

#include <windows.h>

#include <QtCore/QVector>
#include <QtCore/QDebug>
#include <QtCore/QLibrary>
#include <QtCore/QTextStream>

static inline QString msgCannotLoad(const char *lib, const QString &why)
{
    return QString::fromLatin1("Unable load %1: %2").arg(QLatin1String(lib), why);
}

static inline QString msgCannotResolve(const char *lib)
{
    return QString::fromLatin1("Unable to resolve all required symbols in  %1").arg(QLatin1String(lib));
}

namespace utils
{

QString getShortPathName(const QString &name, QString *errorMessage)
{
    typedef DWORD (APIENTRY *GetShortPathNameProtoType)(LPCTSTR, LPTSTR, DWORD);

    if (name.isEmpty())
        return name;

    const char *kernel32DLLC = "kernel32.dll";

    QLibrary kernel32Lib(kernel32DLLC, 0);
    if (!kernel32Lib.isLoaded() && !kernel32Lib.load()) {
        *errorMessage = msgCannotLoad(kernel32DLLC, kernel32Lib.errorString());
        return QString();
    }

    // MinGW requires old-style casts
    GetShortPathNameProtoType getShortPathNameW = (GetShortPathNameProtoType)(kernel32Lib.resolve("GetShortPathNameW"));
    if (!getShortPathNameW) {
        *errorMessage = msgCannotResolve(kernel32DLLC);
        return QString();
    }
    // Determine length, then convert.
    const LPCTSTR nameC = reinterpret_cast<LPCTSTR>(name.utf16()); // MinGW
    const DWORD length = (*getShortPathNameW)(nameC, NULL, 0);
    if (length == 0)
        return name;
    TCHAR *buffer = new TCHAR[length];
    (*getShortPathNameW)(nameC, buffer, length);
    const QString rc = QString::fromUtf16(reinterpret_cast<const ushort *>(buffer), length);
    delete [] buffer;
    return rc;
}

} // namespace utils

#else // #ifdef Q_OS_WIN32
namespace utils
{

QString getShortPathName(const QString &name, QString *)
{
    return name;
}

} // namespace utils

#endif // #ifdef Q_OS_WIN32
