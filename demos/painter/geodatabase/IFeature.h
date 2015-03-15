#ifndef IFEATURE_H
#define IFEATURE_H

#include "geodatabase_api.h"

#include <geometry/GeometryType.h>

#include <QtCore/QRectF>
#include <QtCore/QObject>

class AbstractGeometry;

class GEODATABASE_API IFeature : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int id READ id)
    Q_PROPERTY(Geometry::Type shapeType READ shapeType)
    Q_PROPERTY(QRectF extent READ extent)
    Q_PROPERTY(AbstractGeometry *geometry READ geometry WRITE setGeometry)
public:
    IFeature(){}

    virtual int id() const = 0;
    virtual void setId(int id) = 0;

    virtual const QRectF &extent() const = 0;

    virtual AbstractGeometry *geometry() = 0;
    virtual const AbstractGeometry *geometry() const = 0;

    virtual void setGeometry(AbstractGeometry *geometry) = 0;

    virtual Geometry::Type shapeType() const = 0;

private:
    Q_DISABLE_COPY(IFeature)
};

#endif // IFEATURE_H
