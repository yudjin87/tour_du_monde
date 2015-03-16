#pragma once

#include "geodatabase/geodatabase_api.h"
#include <geometry/GeometryType.h>

#include <QtCore/QObject>

class GEODATABASE_API IRecord : public QObject
{
    Q_OBJECT
public:
    // Read-only for now
    IRecord(){}

    virtual QVariant value(int i) const = 0;
    virtual QVariant value(const QString& name) const = 0;
    // void setValue(int i, const QVariant& val);
    // void setValue(const QString& name, const QVariant& val);

    // void setNull(int i);
    // void setNull(const QString& name);
    virtual bool isNull(int i) const = 0;
    virtual bool isNull(const QString& name) const = 0;

    virtual int indexOf(const QString &name) const = 0;
    virtual QString fieldName(int i) const = 0;

    // QSqlField field(int i) const;
    // QSqlField field(const QString &name) const;

    virtual bool isGenerated(int i) const = 0;
    virtual bool isGenerated(const QString& name) const = 0;
    // void setGenerated(const QString& name, bool generated);
    // void setGenerated(int i, bool generated);

    // void append(const QSqlField& field);
    // void replace(int pos, const QSqlField& field);
    // void insert(int pos, const QSqlField& field);
    // void remove(int pos);

    virtual bool isEmpty() const = 0;
    virtual bool contains(const QString& name) const = 0;
    // void clear();
    // void clearValues();
    virtual int count() const = 0;
    // QSqlRecord keyValues(const QSqlRecord &keyFields) const;

private:
    Q_DISABLE_COPY(IRecord)
};
