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

#ifndef BERRYLISTMODEL_H
#define BERRYLISTMODEL_H

#include <QAbstractListModel>
#include <QQmlListProperty>
#include <QQmlEngine>

class Berry;

class BerryListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_NAMED_ELEMENT(BerryList)
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum Role {
        Name = Qt::UserRole,
        IconPath
    };

    explicit BerryListModel(QObject* parent = nullptr);

    int count() const;
    Q_INVOKABLE Berry* get(int index) const;
    Berry* getByName(const QString& name) const;
    Q_INVOKABLE void append(Berry* data);
    Q_INVOKABLE void remove(int index, int count = 1);
    Q_INVOKABLE void clear();

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    const QList<Berry*>& list() const { return m_data; }

signals:
    void countChanged();

private:
    QList<Berry*> m_data;
};

#endif // BERRYLISTMODEL_H
