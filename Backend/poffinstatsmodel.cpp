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

#include "poffinstatsmodel.h"

PoffinStatsModel::PoffinStatsModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_data.append({QT_TR_NOOP("spicy"), 0, 0, QColor(240, 128, 48), QT_TR_NOOP("coolness")});
    m_data.append({QT_TR_NOOP("dry"), 0, 0, QColor(104, 144, 240), QT_TR_NOOP("beauty")});
    m_data.append({QT_TR_NOOP("sweet"), 0, 0, QColor(248, 88, 136), QT_TR_NOOP("cuteness")});
    m_data.append({QT_TR_NOOP("bitter"), 0, 0, QColor(120, 200, 80), QT_TR_NOOP("cleverness")});
    m_data.append({QT_TR_NOOP("sour"), 0, 0, QColor(248, 208, 48), QT_TR_NOOP("toughness")});
}

QVariant PoffinStatsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        qWarning() << "[PoffinStatsModel] Invalid index";
        return QVariant();
    }

    int i = index.row();
    if (i < 0 && i >= m_data.count())
    {
        qWarning() << "[PoffinStatsModel] Index out of bounds";
        return QVariant();
    }

    const PoffinStat& data = m_data.at(i);

    switch(role)
    {
    case Role::Label:
        return tr(data.label);
    case Role::Key:
        return data.key;
    case Role::Value:
        return data.value;
    case Role::Color:
        return data.color;
    case Role::BonusText:
        return tr(data.bonusText);
    default:
        qWarning() << "[PoffinStatsModel] Unkown role";
    }
    return QVariant();
}

int PoffinStatsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_data.count());
}

QHash<int,QByteArray> PoffinStatsModel::roleNames() const
{
    static QHash<int, QByteArray> _roleNames = {
        {Role::Label, "label"},
        {Role::Key, "key"},
        {Role::Value, "value"},
        {Role::Color, "color"},
        {Role::BonusText, "bonusText"}
    };
    return _roleNames;
}

bool PoffinStatsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        qWarning() << "[PoffinStatsModel] Invalid index";
        return false;
    }

    int i = index.row();
    if (i < 0 && i >= m_data.count())
    {
        qWarning() << "[PoffinStatsModel] Index out of bounds";
        return false;
    }

    PoffinStat& data = m_data[i];

    switch(role)
    {
    case Role::Label:
        //data.label = value.toString();
        break;
    case Role::Key:
        data.key = value.toInt();
        break;
    case Role::Value:
        data.value = value.toInt();
        break;
    case Role::Color:
        data.color = QColor::fromRgba(value.toUInt());
        break;
    default:
        qWarning() << "[PoffinStatsModel] Unkown role";
        return false;
    }
    QList<int> roles = {role};
    emit dataChanged(index, index, roles);
    return true;
}
