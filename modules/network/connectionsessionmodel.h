#ifndef CONNECTIONSESSIONMODEL_H
#define CONNECTIONSESSIONMODEL_H

#include <QObject>
#include <QMap>
#include <QJsonObject>

namespace dcc {

namespace network {

class ConnectionSessionModel : public QObject
{
    Q_OBJECT

    friend class ConnectionSessionWorker;

public:
    explicit ConnectionSessionModel(QObject *parent = 0);

    const QList<QString> sections() const { return m_sections; }
    const QMap<QString, QMap<QString, QJsonObject>> keys() const { return m_keys; }

signals:
    void sectionsChanged(const QList<QString> &sections) const;
    void keysChanged(const QMap<QString, QMap<QString, QJsonObject>> &keys) const;

private slots:
    void setSections(const QList<QString> &sections);
    void setAllKeys(const QString &allKeys);

private:
    QList<QString> m_sections;
    QMap<QString, QString> m_sectionName;
    QMap<QString, QMap<QString, QJsonObject>> m_keys;
};

}

}

#endif // CONNECTIONSESSIONMODEL_H
