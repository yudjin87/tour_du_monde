#ifndef FAKEGEOMETRYFACTORY_H
#define FAKEGEOMETRYFACTORY_H

#include <geometry/IGeometryFactory.h>

#include <QtCore/QObject>

class FakeGeometryFactory : public QObject, public IGeometryFactory
{
public:
    FakeGeometryFactory();
    ~FakeGeometryFactory();

    GeometryType geometryTypeFromShapeType(int shapeType) const override;
    AbstractGeometry *createGeometry(int bytesCount, const char *geometryBlob) const override;

public:
    GeometryType type;
    AbstractGeometry *geometry;
    mutable int createdGeometries;
};

#endif // FAKEGEOMETRYFACTORY_H
