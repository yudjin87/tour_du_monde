#ifndef IFEATURECLASS_H
#define IFEATURECLASS_H

#include "geodatabase_api.h"
#include <geometry/GeometryType.h>

#include <QtCore/QList>
#include <QtCore/QRectF>

class IFeature;

typedef QList<IFeature *> FeatureList;

class GEODATABASE_API IFeatureClass
{
public:
    IFeatureClass(){}
    virtual ~IFeatureClass(){}

    virtual QRectF extent() const = 0;

    virtual GeometryType shapeType() const = 0;

    virtual IFeature &createFeature() = 0;
    virtual const FeatureList &features() const = 0;

private:
    Q_DISABLE_COPY(IFeatureClass)
};

#endif // IFEATURECLASS_H
