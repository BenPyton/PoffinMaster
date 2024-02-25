#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlListProperty>
#include "berrylistmodel.h"
#include "poffin.h"
#include "serializable.h"

class Backend : public QObject, public Serializable
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString version READ version CONSTANT)
    Q_PROPERTY(BerryListModel* berries READ berries NOTIFY berriesChanged)
    Q_PROPERTY(BerryListModel* basket READ basket NOTIFY basketChanged)
    Q_PROPERTY(Poffin* poffin MEMBER m_poffin NOTIFY poffinChanged)

public:
    explicit Backend(QObject *parent = nullptr);
    virtual ~Backend() override;

    QString name() const;
    QString version() const;
    BerryListModel* berries() { return &m_berries; }
    BerryListModel* basket() { return &m_basket; }

    bool load(QString fileName);

    virtual QJsonObject toJson() const override;
    bool fromJson(const QJsonObject& json); // not static because singleton

signals:
    void berriesChanged();
    void basketChanged();
    void poffinChanged();

private slots:
    void onBasketChanged();

private:
    BerryListModel m_berries;
    BerryListModel m_basket;
    Poffin* m_poffin;
};

#endif // BACKEND_H
