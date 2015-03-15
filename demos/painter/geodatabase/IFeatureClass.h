#ifndef IFEATURECLASS_H
#define IFEATURECLASS_H

#include "geodatabase_api.h"
#include <geometry/GeometryType.h>

#include <QtCore/QObject>
#include <QtCore/QVector>
#include <QtCore/QRectF>

class IFeature;
class ISpatialFilter;


class GEODATABASE_API IFeatureClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Geometry::Type shapeType READ shapeType)
    Q_PROPERTY(QRectF extent READ extent)
    Q_PROPERTY(QVector<IFeature *> features READ features)
    Q_PROPERTY(QString source READ source)
public:
    typedef QVector<IFeature *> FeatureList;

public:
    IFeatureClass(){}

    virtual QRectF extent() const = 0;
    virtual Geometry::Type shapeType() const = 0;
    virtual const FeatureList &features() const = 0;

    virtual const QString &source() const = 0;

public slots:
    virtual FeatureList search(const ISpatialFilter &filter) const = 0;
    virtual IFeature *createFeature() = 0;

private:
    Q_DISABLE_COPY(IFeatureClass)
};

#endif // IFEATURECLASS_H
