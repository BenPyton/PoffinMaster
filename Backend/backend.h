/*
 * Copyright 2024 Benoit Pelletier
 *
 * This file is part of Poffin Master.
 * Poffin Master is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * Poffin Master is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Poffin Master. If not, see <https://www.gnu.org/licenses/>.
 */

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
