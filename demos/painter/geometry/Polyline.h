#ifndef POLYLINE_H
#define POLYLINE_H

#include "Polycurve.h"

class GEOMETRY_API Polyline : public Polycurve
{
public:
    Polyline();
    Polyline(const QRectF &extent);

    ~Polyline();
    GeometryType type() const;
};

#endif // POLYLINE_H
