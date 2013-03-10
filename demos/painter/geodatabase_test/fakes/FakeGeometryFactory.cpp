#include "FakeGeometryFactory.h"

//------------------------------------------------------------------------------
FakeGeometryFactory::FakeGeometryFactory()
    : type(GeometryPolyline)
    , geometry(nullptr)
    , createdGeometries(0)
{
}

//------------------------------------------------------------------------------
FakeGeometryFactory::~FakeGeometryFactory()
{
}

//------------------------------------------------------------------------------
GeometryType FakeGeometryFactory::geometryTypeFromShapeType(int shapeType) const
{
    Q_UNUSED(shapeType)
    return type;
}

//------------------------------------------------------------------------------
AbstractGeometry *FakeGeometryFactory::createGeometry(int bytesCount, const char *geometryBlob) const
{
    Q_UNUSED(bytesCount)
    Q_UNUSED(geometryBlob)
    ++createdGeometries;
    return geometry;
}

//------------------------------------------------------------------------------
