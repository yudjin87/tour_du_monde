#pragma once
#include "geodatabase_api.h"

#include <geometry/GeometryType.h>

#include <QtCore/QRectF>
#include <QtCore/QObject>
#include <QtCore/QVector>

class IGeometry;
class IRecord;

class GEODATABASE_API IFeature : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id)
    Q_PROPERTY(Geometry::Type shapeType READ shapeType)
    Q_PROPERTY(QRectF extent READ extent)
    Q_PROPERTY(IRecord *record READ record)
public:
    IFeature(){}

    virtual int id() const = 0;
    virtual void setId(int id) = 0;

    virtual const QRectF &extent() const = 0;

    virtual IGeometry *geometry() = 0;
    virtual const IGeometry *geometry() const = 0;

    virtual void setGeometry(IGeometry *geometry) = 0;

    virtual Geometry::Type shapeType() const = 0;

    virtual IRecord* record() = 0;
    virtual const IRecord* record() const = 0;

private:
    Q_DISABLE_COPY(IFeature)
};

typedef QVector<IFeature *> IFeatureCollection;

