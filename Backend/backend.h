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
    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)
    Q_PROPERTY(QString author READ authorName CONSTANT)
    Q_PROPERTY(QString license READ licenseName CONSTANT)
    Q_PROPERTY(QString licenseUrl READ licenseUrl CONSTANT)
    Q_PROPERTY(QString sourceUrl READ sourceUrl CONSTANT)
    Q_PROPERTY(bool debug READ isDebug CONSTANT)
    Q_PROPERTY(BerryListModel* berries READ berries NOTIFY berriesChanged)
    Q_PROPERTY(BerryListModel* basket READ basket NOTIFY basketChanged)
    Q_PROPERTY(Poffin* poffin MEMBER m_poffin NOTIFY poffinChanged)

public:
    explicit Backend(QObject *parent = nullptr);
    virtual ~Backend() override;

    // App details
    QString name() const;
    QString version() const;
    QString qtVersion() const;
    QString authorName() const;
    QString licenseName() const;
    QString licenseUrl() const;
    QString sourceUrl() const;
    bool isDebug() const;

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
