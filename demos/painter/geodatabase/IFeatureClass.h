#ifndef IFEATURECLASS_H
#define IFEATURECLASS_H

#include "geodatabase/geodatabase_api.h"
#include "geodatabase/IFeature.h"
#include <geometry/GeometryType.h>

#include <QtCore/QObject>
#include <QtCore/QRectF>

class ISpatialFilter;

class GEODATABASE_API IFeatureClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Geometry::Type shapeType READ shapeType)
    Q_PROPERTY(QRectF extent READ extent)
    Q_PROPERTY(QString source READ source)
public:
    IFeatureClass(){}

    virtual QRectF extent() const = 0;
    virtual Geometry::Type shapeType() const = 0;
    virtual const IFeature *featureById(const int id) const = 0;

    virtual const QString &source() const = 0;

public slots:
    virtual IFeatureCollection search(const ISpatialFilter &filter) const = 0;
    virtual IFeature *createFeature() = 0;

private:
    Q_DISABLE_COPY(IFeatureClass)
};

#endif // IFEATURECLASS_H
