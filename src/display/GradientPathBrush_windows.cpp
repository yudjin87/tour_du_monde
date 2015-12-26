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

#include "display/GradientPathBrush.h"
#include "display/GradientFillSymbol.h"
#include "display/LineSymbol.h"

#include <geometry/Polygon.h>
#include <geometry/Point.h>
#include <geometry/Ring.h>

#include <QtGui/QPainter>
#include <QtGui/QPaintDevice>
#include <QtGui/QPainterPath>
#include <QtGui/QTransform>
#include <QDebug>

#include <windows.h>
#include <Gdiplus.h>
#include <objidl.h>

namespace
{
int initGdiPlus();
}

GradientPathBrush::GradientPathBrush(GradientFillSymbol &symbol)
    : QObject(&symbol)
    , m_symbol(symbol)
{
    static int init = initGdiPlus();
    Q_UNUSED(init)
}

GradientPathBrush::GradientPathBrush(const GradientPathBrush &o, GradientFillSymbol &symbol)
    : QObject(&symbol)
    , m_symbol(symbol)
{
}

GradientPathBrush *GradientPathBrush::clone(GradientFillSymbol &symbol) const
{
    return new GradientPathBrush(*this, symbol);
}

void GradientPathBrush::prepare(QPainter *painter)
{
//    const int width = painter->device()->width();
//    const int height = painter->device()->height();

//    // Define the header
//    BITMAPINFO bmi;
//    memset(&bmi, 0, sizeof(bmi));
//    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
//    bmi.bmiHeader.biWidth       = static_cast<LONG>(width);
//    bmi.bmiHeader.biHeight      = -static_cast<LONG>(height);
//    bmi.bmiHeader.biPlanes      = 1;
//    bmi.bmiHeader.biBitCount    = 32;
//    bmi.bmiHeader.biCompression = BI_RGB;
//    bmi.bmiHeader.biSizeImage   = static_cast<LONG>(width) * static_cast<LONG>(height) * 4;

//    HDC display_dc = GetDC(0);
//    HDC memDC = ::CreateCompatibleDC(display_dc);

//    // Create the pixmap
//    uchar *pixels = 0;
//    HBITMAP bitmap = ::CreateDIBSection(display_dc, &bmi, DIB_RGB_COLORS, (void **) &pixels, 0, 0);
//    HBITMAP old_hBitmap = (HBITMAP)::SelectObject(memDC, bitmap);
}

void GradientPathBrush::drawingFinished(QPainter *painter)
{

}

void GradientPathBrush::drawPolygon(const RingList &rings, QPainter &painter)
{
    const QTransform& transform = painter.transform();

    const int width = painter.device()->width();
    const int height = painter.device()->height();
    // Define the header
    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = static_cast<LONG>(width);
    bmi.bmiHeader.biHeight      = -static_cast<LONG>(height);
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage   = static_cast<LONG>(width) * static_cast<LONG>(height) * 4;

    HDC display_dc = GetDC(0);
    HDC memDC = ::CreateCompatibleDC(display_dc);

    // Create the pixmap
    uchar *pixels = nullptr;
    HBITMAP bitmap = ::CreateDIBSection(display_dc, &bmi, DIB_RGB_COLORS, (void **) &pixels, 0, 0);
    HBITMAP old_hBitmap = (HBITMAP)::SelectObject(memDC, bitmap);

    Gdiplus::Matrix nativeTransformMatrix(
                static_cast<Gdiplus::REAL>(transform.m11()),
                static_cast<Gdiplus::REAL>(transform.m12()),
                static_cast<Gdiplus::REAL>(transform.m21()),
                static_cast<Gdiplus::REAL>(transform.m22()),
                static_cast<Gdiplus::REAL>(transform.dx()),
                static_cast<Gdiplus::REAL>(transform.dy()));

    Gdiplus::Graphics graphics(memDC);
    graphics.SetTransform(&nativeTransformMatrix);

    // TODO: prepare it inside prepare/drawingFinished
    Gdiplus::GraphicsPath path;

    for (const Ring* ring : rings)
    {
        //std::unique_ptr<Gdiplus::PointF[]> points(new Gdiplus::PointF[ring->points().size()]);
        Gdiplus::PointF* points(new Gdiplus::PointF[ring->points().size()]);
        for (int i = 0; i < ring->points().size(); ++i)
        {
            const Point* p = ring->points()[i];
            points[i].X = static_cast<Gdiplus::REAL>(p->x());
            points[i].Y = static_cast<Gdiplus::REAL>(p->y());
        }
        path.AddPolygon(points, ring->points().size());
    }

    Gdiplus::PathGradientBrush pthGrBrush(&path);

    const QColor& centralColor = m_symbol.centralColor();
    pthGrBrush.SetCenterColor(Gdiplus::Color(255, centralColor.red(), centralColor.green(), centralColor.blue()));

    const QColor& surroundColor = m_symbol.surroundColor();
    Gdiplus::Color colors[] = {Gdiplus::Color(255, surroundColor.red(), surroundColor.green(), surroundColor.blue())};
    INT count = 1;
    pthGrBrush.SetSurroundColors(colors, &count);

    const Gdiplus::REAL triangulaFocus = static_cast<const Gdiplus::REAL>(m_symbol.triangularBellShapeFocus());
    const Gdiplus::REAL triangulaScale = static_cast<const Gdiplus::REAL>(m_symbol.triangularBellShapeScale());
    pthGrBrush.SetBlendTriangularShape(triangulaFocus, triangulaScale);

    const Gdiplus::REAL focus = static_cast<const Gdiplus::REAL>(m_symbol.bellShapeFocus());
    const Gdiplus::REAL scale = static_cast<const Gdiplus::REAL>(m_symbol.bellShapeScale());
    pthGrBrush.SetBlendBellShape(focus, scale);

    const Gdiplus::REAL factor1 = static_cast<const Gdiplus::REAL>(m_symbol.blendFactor1());
    const Gdiplus::REAL factor2 = static_cast<const Gdiplus::REAL>(m_symbol.blendFactor2());
    const Gdiplus::REAL position1 = static_cast<const Gdiplus::REAL>(m_symbol.blendPosition1());
    const Gdiplus::REAL position2 = static_cast<const Gdiplus::REAL>(m_symbol.blendPosition2());

    const Gdiplus::REAL factors[] = {0.0f, factor1, factor2, 1.0f};
    const Gdiplus::REAL positions[] = {0.0f, position1, position2, 1.0f};
    pthGrBrush.SetBlend(factors, positions, 4);

    pthGrBrush.SetGammaCorrection(TRUE);

    graphics.FillPath(&pthGrBrush, &path);

    const QColor& penColor = m_symbol.outline()->color();
    Gdiplus::Pen pen(Gdiplus::Color(255, penColor.red(), penColor.green(), penColor.blue()), m_symbol.outline()->width());

    nativeTransformMatrix.Invert();
    pen.SetTransform(&nativeTransformMatrix);

    graphics.DrawPath(&pen, &path);

    // Create image and copy data into image.
    QImage image(width, height, QImage::Format_ARGB32_Premultiplied);
    uint mask = 0;
    if (image.isNull()) { // failed to alloc?
        ReleaseDC(0, display_dc);
        qWarning("%s, failed create image of %dx%d", __FUNCTION__, width, height);
        return;
    }
    const int bytes_per_line = width * sizeof(QRgb);
    for (int y = 0; y < height; ++y) {
        QRgb *dest = (QRgb *) image.scanLine(y);
        const QRgb *src = (const QRgb *) (pixels + y * bytes_per_line);
        for (int x = 0; x < width; ++x) {
            const uint pixel = src[x];
            if ((pixel & 0xff000000) == 0 && (pixel & 0x00ffffff) != 0)
                dest[x] = pixel | 0xff000000;
            else
                dest[x] = pixel | mask;
        }
    }

    //----------------

    ::SelectObject(memDC, old_hBitmap);
    ::DeleteObject(bitmap);
    ::DeleteDC(memDC);
    ::ReleaseDC(0, display_dc);

    painter.setWorldMatrixEnabled(false);
    painter.drawImage(QPoint(0, 0), image);
    painter.setWorldMatrixEnabled(true);
}

namespace
{
int initGdiPlus()
{
Gdiplus::GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;
Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
return 0;
}

}
