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

#include "berrylistmodel.h"
#include "berry.h"
#include <algorithm>

BerryListModel::BerryListModel(QObject* parent)
    : QAbstractListModel{parent}
{}

int BerryListModel::count() const
{
    return static_cast<int>(m_data.count());
}

Berry* BerryListModel::get(int index) const
{
    if (index >= 0 && index < count())
        return m_data[index];
    return nullptr;
}

Berry* BerryListModel::getByName(const QString& name) const
{
    const auto it = std::find_if(m_data.cbegin(), m_data.cend(), [&name] (Berry* element) {
        return (element != nullptr) && (element->name().toLower() == name);
    });

    if (it == m_data.cend())
        return nullptr;
    return *it;
}

void BerryListModel::append(Berry* data)
{
    int index = static_cast<int>(m_data.count());
    beginInsertRows(QModelIndex(), index, index);
    m_data.append(data);
    endInsertRows();
    emit countChanged();
}

void BerryListModel::remove(int index, int count)
{
    beginRemoveRows(QModelIndex(), index, index + count - 1);
    m_data.remove(index);
    endRemoveRows();
    emit countChanged();
}

void BerryListModel::clear()
{
    removeRows(0, count());
    emit countChanged();
}

QVariant BerryListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        qWarning() << "[BerryListModel] Invalid index";
        return QVariant();
    }

    int i = index.row();
    if (i < 0 && i >= m_data.count())
    {
        qWarning() << "[BerryListModel] Index out of bounds";
        return QVariant();
    }

    Berry* berry = m_data.at(i);
    if (berry == nullptr)
    {
        qWarning() << "[BerryListModel] Berry is null";
        return QVariant();
    }

    switch(role)
    {
        case Role::Name:
            return berry->name();
        case Role::IconPath:
            return berry->iconPath();
        default:
            qWarning() << "[BerryListModel] Unkown role";
    }
    return QVariant();
}

int BerryListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return static_cast<int>(m_data.count());
}

QHash<int,QByteArray> BerryListModel::roleNames() const
{
    static QHash<int, QByteArray> s_roleNames = {{Role::Name, "name"}, {Role::IconPath, "iconPath"}};
    return s_roleNames;
}
