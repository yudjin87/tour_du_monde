#ifndef FAKEDEFINITIONPARSER_H
#define FAKEDEFINITIONPARSER_H

#include <componentsystem/IDefinitionParser.h>
#include <QtCore/QObject>

class FakeDefinitionParser : public QObject, public IDefinitionParser
{
    Q_OBJECT
public:
    FakeDefinitionParser();

    const QString &error() const;
    const QString &componentName() const;
    const QString &componentLocation() const;
    const QString &description() const;
    const QStringList &parents() const;
    const QString &productName() const;
    const QString &provider() const;
    bool read(const QString &text);
    bool read(const QByteArray &data);
    bool read(QIODevice* dev);

signals:
    void readCalled();

public:
    QString m_componentName;
    QString m_componentLocation;
    QString m_description;
    QString m_productName;
    QString m_provider;
    QString m_error;
    QStringList m_parents;
};

#endif // FAKEDEFINITIONPARSER_H
