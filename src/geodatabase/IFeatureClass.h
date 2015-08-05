#pragma once
#include "geodatabase/geodatabase_api.h"
#include "geodatabase/IDataset.h"
#include "geodatabase/IFeature.h"

#include <geometry/GeometryType.h>

#include <QtCore/QObject>
#include <QtCore/QRectF>

#include <memory>

class ISpatialFilter;
class ITable;

class GEODATABASE_API IFeatureClass : public IDataset
{
    Q_OBJECT
    Q_PROPERTY(Geometry::Type shapeType READ shapeType)
    Q_PROPERTY(QRectF extent READ extent)
    Q_PROPERTY(int featuresCount READ featuresCount)
public:
    IFeatureClass(){}

    virtual QRectF extent() const = 0;
    virtual Geometry::Type shapeType() const = 0;

    // by record id (from shapefiles), or DB id. Id starts from 1
    virtual const IFeature *featureById(const int id) const = 0;

    // Index starts from 0
    virtual const IFeature *featureByIndex(const int index) const = 0;

    virtual const ITable* table() const = 0;
    virtual int featuresCount() const = 0;

public slots:
    virtual IFeatureCollection search(const ISpatialFilter &filter) const = 0;
    virtual IFeature *createFeature() = 0;

private:
    Q_DISABLE_COPY(IFeatureClass)
};

typedef std::unique_ptr<IFeatureClass> IFeatureClassUPtr;

