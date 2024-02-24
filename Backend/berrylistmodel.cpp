#include "berrylistmodel.h"
#include "berry.h"

BerryListModel::BerryListModel() {}

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
    static QHash<int, QByteArray> _roleNames = {{Role::Name, "name"}, {Role::IconPath, "iconPath"}};
    return _roleNames;
}
