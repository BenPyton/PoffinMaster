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

#ifndef POFFINSTATSMODEL_H
#define POFFINSTATSMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <QColor>

struct PoffinStat
{
    const char* label;
    int key;
    int value;
    QColor color;
    const char* bonusText;
};

class PoffinStatsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Role {
        Label = Qt::UserRole,
        Key,
        Value,
        Color,
        BonusText
    };

    explicit PoffinStatsModel(QObject *parent = nullptr);

    int count() const { return static_cast<int>(m_data.count()); }

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QHash<int,QByteArray> roleNames() const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    const QList<PoffinStat>& list() const { return m_data; }

    int statValue(int index) const { return m_data[index].value; }
    void setStatValue(int index, int value) {
        setData(this->index(index), value, Role::Value);
    }

    const char* statName(int index) const { return m_data[index].label; }

signals:
    void countChanged();

private:
    int m_maxTotal = 0;
    QList<PoffinStat> m_data;
};

#endif // POFFINSTATSMODEL_H
